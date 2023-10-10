#include "vex.h"
#include "../Odometry/Odometry.h"

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

    double radiansToDegrees(double radians)
    {
    }

public:
    /// @brief This method will move the robot to a position on the field
    /// @param targetX The x position that you want the robot to move to on the field
    /// @param targetY The y position that you want the robot to move to on the field
    /// @param targetTheta The angle at which you want the robot to be at once it is done moving
    /// @param isRelativeToZero Whether the x and y values are based off of the assumption that the robot is always starting at point (0, 0)
    void MoveToPoint(double targetX, double targetY, double targetTheta = NULL, bool isRelativeToZero = false)
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
        double turnAngle = 0;

        // Constants
        float kP = 0.01;
        float kI = 0.01;
        float kD = 0.01;

        float turnkP = 0.01;
        float turnkI = 0.01;
        float turnkD = 0.01;
        int maxErrorForIntegral = 100;
        int maxTurnErrorForTurnIntegral = 90;
        int dT = 15;

        if (!isRelativeToZero)
        {
            while (error >= 3 || (error < 0 && error >= -3))
            {
                /*=================================================================
                                    Moving towards target point
                =================================================================*/

                /*****************************ERROR*****************************/
                error = sqrt(fabs(pow(targetX - x, 2)) + fabs(pow(targetY - y, 2)));

                /*****************************INTEGRAL*****************************/
                // If the robot has overshot the target or the error is really big then integral should be 0
                error < 0 || error >= maxErrorForIntegral ? integral = 0 : integral += error;

                /*****************************DERIVATIVE*****************************/
                derivative = error - previousError;

                /*=================================================================
                                    Turning towards target point
                =================================================================*/

                /*****************************TURN ERROR*****************************/
                angle = atan2(targetY - y, targetX - x) * (180 / M_PI);
                if (angle < 0)
                    angle += 360;
                turnError = this->findMinAngle(angle, theta);

                /*****************************TURN INTEGRAL*****************************/
                turnError < 0 || turnError >= maxTurnErrorForTurnIntegral ? turnIntegral = 0 : turnIntegral += turnError;

                /*****************************TURN DERIVATIVE*****************************/
                turnDerivative = turnError - previousTurnError;

                // Calculate the powers for going straight and turning
                power = (error * kP) + (integral * kI) + (derivative * kD);
                turnPower = (turnError * turnkP) + (turnIntegral * turnkI) + (turnDerivative * turnkD);

                // Spin the motors based on the values
                Right.spin(vex::directionType::fwd, power + turnPower, vex::voltageUnits::volt);
                Left.spin(vex::directionType::fwd, power - turnPower, vex::voltageUnits::volt);

                // Update the previous errors
                previousError = error;
                previousTurnError = turnError;

                wait(dT, vex::timeUnits::msec);
            }
        }
    }

    /// @brief This method will turn the robot to a certain angle relative to the field
    /// @param targetTheta This is the angle at which you want the robot to turn to
    void Turn(double targetTheta)
    {
        double turnPower = 0;

        // PID components
        double turnError = 3;
        double previousTurnError = 0;

        double turnIntegral = 0;

        double turnDerivative = 0;

        // Constants
        float turnkP = 0.01;
        float turnkI = 0.01;
        float turnkD = 0.01;
        int maxTurnErrorForTurnIntegral = 90;
        int dT = 15;

        while (turnError >= 3 || turnError <= -3)
        {
            /*****************************TURN ERROR*****************************/
            turnError = this->findMinAngle(targetTheta, theta);

            /*****************************TURN INTEGRAL*****************************/
            turnError < 0 || turnError >= maxTurnErrorForTurnIntegral ? turnIntegral = 0 : turnIntegral += turnError;

            /*****************************TURN DERIVATIVE*****************************/
            turnDerivative = turnError - previousTurnError;

            // Calculate the power for each of the motors
            turnPower = (turnError * turnkP) + (turnIntegral * turnkI) + (turnDerivative * turnkD);

            // Make the motors spin
            Right.spin(vex::directionType::fwd, turnPower, vex::voltageUnits::volt);
            Left.spin(vex::directionType::fwd, -turnPower, vex::voltageUnits::volt);

            previousTurnError = turnError;

            wait(dT, vex::timeUnits::msec);
        }
    }
};