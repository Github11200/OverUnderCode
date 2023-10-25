#include "../../include/Autonomous/PurePursuit.h"

using namespace vex;

Point::Point(double x, double y, double speed, double lookAheadDistance)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->lookAheadDistance = lookAheadDistance;
}

int PurePursuit::sgn(double num)
{
    if (num >= 0)
        return 1;
    else
        return -1;
}

bool PurePursuit::isInRange(double num, double target, double range)
{
    if (num >= target - range && num <= target + range)
        return true;
    else
        return false;
}

double PurePursuit::dist(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(fabs(x2 - x1), 2) + pow(fabs(y2 - y1), 2));
}

Point PurePursuit::chooseGoalPoint()
{
    // Create the goal point which is what will be returned
    Point goalPt(0, 0, 0, 0);

    // Loop through all the points starting from the one that we ended at in the
    // last call of this method
    for (int i = this->lastFoundIndex; i < this->pointsLength - 1; ++i)
    {
        // Get the current point and the next point
        Point pointOne = this->Points[i];
        Point pointTwo = this->Points[i + 1];

        // Get the coordinates of the first and second point, and make the coordinates
        // centered at 0 by substracting the current position of the robot
        double x1 = pointOne.x - x;
        double y1 = pointOne.y - y;
        double x2 = pointTwo.x - x;
        double y2 = pointTwo.y - y;

        // Calculate the variables required for the quadratic formula
        double dx = x2 - y1;
        double dy = y2 - y1;
        double dr = sqrt(pow(dx, 2) + pow(dy, 2));
        double D = x1 * y2 - x2 * y1;

        // Find the discriminant
        double discriminant = pow(pointTwo.lookAheadDistance, 2) * pow(dr, 2) - pow(D, 2);

        // If solutions don't exist (in that case the discriminant woulud be less than 0)
        // or we have reached the end of the path and point one and point two are equal to
        // each other, then just continue
        if (discriminant < 0 || (pointOne.x == pointTwo.x && pointOne.y == pointTwo.y))
            continue;

        // Since solutions exist, calculate both solutions
        double x1Sol = (D * dy + this->sgn(dy) * dx * sqrt(discriminant)) / pow(dr, 2);
        double x2Sol = (D * dy - this->sgn(dy) * dx * sqrt(discriminant)) / pow(dr, 2);
        double y1Sol = (-D * dx + fabs(dy) * sqrt(discriminant)) / pow(dr, 2);
        double y2Sol = (-D * dx - fabs(dy) * sqrt(discriminant)) / pow(dr, 2);

        // Create two objects with the coordinates of the solutions
        Point sol1(x1Sol + x, y1Sol + y, pointTwo.speed, pointTwo.lookAheadDistance);
        Point sol2(x2Sol + x, y2Sol + y, pointTwo.speed, pointTwo.lookAheadDistance);

        // Calculate min and max values for the coordinates for both points
        double minX = min(pointOne.x, pointTwo.x);
        double maxX = max(pointOne.x, pointTwo.x);
        double minY = min(pointOne.y, pointTwo.y);
        double maxY = max(pointOne.y, pointTwo.y);

        // Figure out which one of the points are valid, and are within the two points
        bool validPointOne = minX <= sol1.x && sol1.x <= maxX && minY <= sol1.y && sol1.y <= maxY;
        bool validPointTwo = minX <= sol2.x && sol2.x <= maxX && minY <= sol2.y && sol2.y <= maxY;

        // This entire block is to just check whether the robot is at the end or not, and this if
        // statement checks whether the number of points of more than 0
        if (this->pointsLength > 0)
        {
            // Figure out the coordinates of the last point in the path
            double endX = this->Points[this->pointsLength - 1].x;
            double endY = this->Points[this->pointsLength - 1].y;

            // Check if the robot is already at the end of the path
            if (this->isInRange(x, endX, 1) && this->isInRange(y, endY, 1))
                return goalPt;

            // Again check whether the robot is at the end of the path by figuring out the length of the
            // hypoteneuse and check if that is less than a certain amount of the look ahead distance
            if (sqrt(pow(endX - x, 2) + pow(endY - y, 2)) <= pointTwo.lookAheadDistance - (pointTwo.lookAheadDistance - 2))
                return goalPt;

            // Check whether the distance between the robot and the last point in the path
            // is less than the look ahead distance, and if it is then just return the goal
            // point because the robot has not yet reached the end
            if (sqrt(pow(endX - x, 2) + pow(endY - y, 2)) <= pointTwo.lookAheadDistance)
            {
                goalPt.x = endX;
                goalPt.y = endY;
                goalPt.lookAheadDistance = pointTwo.lookAheadDistance;
                goalPt.speed = pointTwo.speed;
                return goalPt;
            }
        }

        // Check if either of the points in the path are valid
        if (validPointOne || validPointTwo)
        {
            // If the first point is valid, then make goal point equal to the first solution
            if (validPointOne)
                goalPt = sol1;

            // Check if the second point is also valid
            if (validPointTwo)
            {
                // Check whether the goal point has been assigned a value, in which case goal point has
                // to equal to solution 2. Also check which solution is closer to the second point in
                // the path because if the second solution is closer then goal point should be set to that
                if (goalPt.lookAheadDistance == 0 || abs(x1Sol - x2) > abs(x2Sol - x2) || abs(y1Sol - y2) > abs(y2Sol - y2))
                    goalPt = sol2;
            }

            // This condition just makes sure that the robot won't move backwards
            if (this->dist(goalPt.x, goalPt.y, pointTwo.x, pointTwo.y) < this->dist(x, y, pointTwo.x, pointTwo.y))
                break;
            else
                ++this->lastFoundIndex;
        }
    }

    return goalPt;
}