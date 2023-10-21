#include "vex.h"
#include "../../global-variables.h"

using namespace vex;

class PID
{
private:
    /// @brief This function returns 1 or -1 based on whether the input number is positive or negative
    /// @param num The number who's sign you want to figure out
    /// @return 1 or -1 based on whether the input number is positive or negative
    int sgn(double num)
    {
        if (num >= 0)
            return 1;
        else
            return -1;
    }

    /// @brief This method finds the minimum angle that the robot has to turn in order to face the target angle
    /// @param targetAngle This is the angle at which we want the robot to be at
    /// @param currentHeading This is the angle at which the robot is currently at
    /// @return The minimum number of degrees the robot has to turn to reach the target angle
    double findMinAngle(double targetAngle, double currentHeading)
    {
        double minAngle = targetAngle - currentHeading;

        if (minAngle > 180 || minAngle < -180)
            minAngle = -1 * this->sgn(minAngle) * (360 - fabs(minAngle));

        return minAngle;
    }

    /// @brief  This method converts an input of inches to how many degrees the motors have to turn
    /// @param inches is how many inches you want the motor to move
    /// @return A float that tells you how many degrees the motors have to rotate
    float Inches_To_Degrees(float inches)
    {
        float Wheel_Circumfrance = 2 * M_PI * 2;

        float degrees = (inches / Wheel_Circumfrance) * 360;

        return degrees;
    }

public:
    /// @brief This method will move the robot to a position on the field
    /// @param targetX The x position that you want the robot to move to on the field in inches
    /// @param targetY The y position that you want the robot to move to on the field in inches
    /// @param targetTheta The angle at which you want the robot to be at once it is done moving in degrees
    /// @param isRelativeToZero Whether the x and y values are based off of the assumption that the robot is always starting at point (0, 0)
    /// @param desiredValue This parameter is used as the target position if the starting point of the PID is from 0 in inches
    void MoveToPoint(double targetX, double targetY, double targetTheta = NULL, bool isRelativeToZero = false, double desiredValue = 10000, double turnkPValue = 0.211, double errorLoopEndValue = 0.8, double turnErrorLoopEndValue = 2, double kpValue = 0.85)
    {
        // The total power for turning and moving forward
        double power = 0;
        double turnPower = 0;

        // The errors both while moving forward and turning
        double error = 10;
        double previousError = 0;
        double turnError = 0;
        double previousTurnError = 0;

        double integral = 0;
        double turnIntegral = 0;

        double derivative = 0;
        double turnDerivative = 0;

        double angle = 0;

        // Constants
        float kP = kpValue;
        float kI = 0.01;
        float kD = 0.01;
        float wheelDiameter = 4;

        float turnkP = turnkPValue;
        float turnkI = 0.08;
        float turnkD = 0.05;
        int maxErrorForIntegral = 100;
        int maxTurnErrorForTurnIntegral = 90;
        int dT = 15;

        double leftPositionAverage = 0;
        double rightPositionAverage = 0;
        double averagePosition = 0;
        double inchesTraveled = 0;

        // If the robot's starting position is going to be from 0 every time (if we don't have time
        // to implement odometry) then set the position to 0 always
        if (isRelativeToZero)
        {
            Left.setPosition(0, vex::rotationUnits::deg);
            Right.setPosition(0, vex::rotationUnits::deg);
        }

        while (fabs(error) >= errorLoopEndValue || fabs(turnError) >= turnErrorLoopEndValue)
        {
            cout << "Error: " << error << endl;
            cout << "Turn Error: " << turnError << endl;
            cout << "Turn Power: " << turnPower << endl;
            cout << "Power: " << power << endl;

            // If the robot is starting relative to 0 then the average position will the the average
            // between the motors on the left side and the motors on the right side
            if (isRelativeToZero)
            {
                leftPositionAverage = -((FrontLeft.position(vex::rotationUnits::deg) + BackLeft.position(vex::rotationUnits::deg)) / 2);
                rightPositionAverage = ((FrontRight.position(vex::rotationUnits::deg) + BackRight.position(vex::rotationUnits::deg)) / 2);
                averagePosition = (leftPositionAverage + rightPositionAverage) / 2;
                inchesTraveled = ((averagePosition / 840) * wheelDiameter * M_PI);
            }

            /*=================================================================
                                Moving towards target point
            =================================================================*/

            /*****************************ERROR*****************************/
            error = (desiredValue - inchesTraveled);

            /*=================================================================
                                Turning towards target point
            =================================================================*/

            /*****************************TURN ERROR*****************************/
            // angle = atan2(targetY - y, targetX - x) * (180 / M_PI);
            // if (angle < 0)
            //     angle += 360;
            turnError = this->findMinAngle(targetTheta, Inertial.heading(vex::rotationUnits::deg));

            // /*****************************TURN DERIVATIVE*****************************/
            turnDerivative = turnError - previousTurnError;

            // Calculate the powers for going straight and turning
            power = (error * kP);
            turnPower = ((turnError * turnkP) + (turnDerivative * turnkD));

            // Spin the motors based on the values
            Left.spin(vex::directionType::rev, power + turnPower, vex::voltageUnits::volt);
            Right.spin(vex::directionType::fwd, power - turnPower, vex::voltageUnits::volt);

            // Update the previous errors
            previousError = error;
            previousTurnError = turnError;

            wait(dT, vex::timeUnits::msec);
        }

        cout << "DONE MOVING TO POINT//////////////////////////////////////////////////////////" << endl;
    }

    /// @brief This method will turn the robot to a certain angle relative to the field
    /// @param targetTheta This is the angle at which you want the robot to turn to in degrees
    void Turn(double targetTheta, double turnkPValue = 0.2, double errorValue = 1.9)
    {
        double turnPower = 0;

        // PID components
        double turnError = 10;
        double previousTurnError = 0;

        double turnIntegral = 0;

        double turnDerivative = 0;

        // Constants
        float turnkP = turnkPValue;
        float turnkI = 0.01;
        float turnkD = 0.02;
        int maxTurnErrorForTurnIntegral = 60;
        int dT = 15;

        while (fabs(turnError) >= errorValue)
        {
            /*****************************TURN ERROR*****************************/
            turnError = this->findMinAngle(targetTheta, Inertial.heading(vex::rotationUnits::deg));

            /*****************************TURN INTEGRAL*****************************/
            fabs(turnError) < 0 || fabs(turnError) >= maxTurnErrorForTurnIntegral ? turnIntegral = 0 : turnIntegral += turnError;

            /*****************************TURN DERIVATIVE*****************************/
            // turnDerivative = turnError - previousTurnError;

            // Calculate the power for each of the motors
            turnPower = (turnError * turnkP) + (turnDerivative * turnkD);

            cout << "Turn error: " << turnError << endl;
            cout << "Turn power: " << turnPower << endl;
            cout << "Inertial heading: " << Inertial.heading(deg) << endl;

            // Make the motors spin
            Right.spin(vex::directionType::rev, turnPower, vex::voltageUnits::volt);
            Left.spin(vex::directionType::fwd, -turnPower, vex::voltageUnits::volt);

            previousTurnError = turnError;

            wait(dT, vex::timeUnits::msec);
        }

        cout << "Done turning" << endl;
    }

    /// @brief This method gets the robot to just drive straight, but it doesn't use a PID so it goes quite fast and is used for shorter distances that don't require a lot of accuracy
    /// @param drive_distance is how far you want the robot to drive
    /// @param speed is the speed at which you want the robot to drive
    /// @return Void
    void drive_straight(float drive_distance, float speed)
    {
        // Get how many degrees the left side and right side motors have to turn
        float drive_degrees = Inches_To_Degrees(drive_distance);

        // Spin the motors
        Left.spinFor(vex::directionType::fwd, -drive_degrees, vex::rotationUnits::deg, speed, vex::velocityUnits::pct, false);
        Right.spinFor(vex::directionType::rev, -drive_degrees, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
    }
};