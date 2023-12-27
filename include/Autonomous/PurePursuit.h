#ifndef PURE_PURSUIT_H
#define PURE_PURSUIT_H

#include "vex.h"
#include "../global-variables.h"
#include <vector>
#include <math.h>

using namespace vex;
using namespace std;

/// @brief This structure defines one point in a path
struct Point
{
    double x;
    double y;
    double orientation;
    double lookAheadDistance;

    Point(double x, double y, double orientation, double lookAheadDistance);
};

class PurePursuit
{
private:
    vector<Point> Points = {};
    int pointsLength = Points.size();
    int lastFoundIndex = 0;

    /// @brief This function returns 1 or -1 based on whether the input number is positive or negative
    /// @param num The number who's sign you want to figure out
    /// @return 1 or -1 based on whether the input number is positive or negative
    int sgn(double num);

    /// @brief This method checks if a number is within the range of another number
    /// @param num The input number
    /// @param target The number that is in the middle of the range
    /// @param range How much you can add and subtract from the target, which creates the range
    /// @return A boolean value indicating whether the input number is within the range
    bool isInRange(double num, double target, double range);

    /// @brief This method finds the distance between two points by finding the hypotenuse of a triangle
    /// @param x1 The x coordinate of the first point
    /// @param y1 The y coordinate of the first point
    /// @param x2 The x coordinate of the second point
    /// @param y2 The y coordinate of the second point
    /// @return The distance between two points
    double dist(double x1, double y1, double x2, double y2);

public:
    /// @brief This method finds out what the best goal point is for the robot to follow
    /// @return A point which has the x and y coordinates, speed, and the look ahead distance
    Point chooseGoalPoint();

    /// @brief This method will execute the path given to it
    /// @param Points These are the points along the path
    void executePath(vector<Point> Points);
};

#endif