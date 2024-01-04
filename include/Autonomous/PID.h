#ifndef PID_H
#define PID_H

#include "vex.h"
#include "Odometry.h"

class PID
{
private:
    /// @brief This function returns 1 or -1 based on whether the input number is positive or negative
    /// @param num The number who's sign you want to figure out
    /// @return 1 or -1 based on whether the input number is positive or negative
    int sgn(double num);

    /// @brief This method finds the minimum angle that the robot has to turn in order to face the target angle
    /// @param targetAngle This is the angle at which we want the robot to be at
    /// @param currentHeading This is the angle at which the robot is currently at
    /// @return The minimum number of degrees the robot has to turn to reach the target angle
    double findMinAngle(double targetAngle, double currentHeading);

    /// @brief  This method converts an input of inches to how many degrees the motors have to turn
    /// @param inches is how many inches you want the motor to move
    /// @return A float that tells you how many degrees the motors have to rotate
    float Inches_To_Degrees(float inches);

    /// @brief This method checks if a number is within the range of another number
    /// @param num The input number
    /// @param target The number that is in the middle of the range
    /// @param range How much you can add and subtract from the target, which creates the range
    /// @return A boolean value indicating whether the input number is within the range
    bool isInRange(double num, double target, double range);

public:
    /// @brief This method will move the robot to a position on the field
    /// @param targetX The x position that you want the robot to move to on the field in inches
    /// @param targetY The y position that you want the robot to move to on the field in inches
    /// @param targetTheta The angle at which you want the robot to be at once it is done moving in degrees
    /// @param isRelativeToZero Whether the x and y values are based off of the assumption that the robot is always starting at point (0, 0)
    /// @param desiredValue This parameter is used as the target position if the starting point of the PID is from 0 in inches
    void MoveToPoint(
        double targetX,
        double targetY,
        double errorConstants[3],
        double turnErrorConstants[3],
        double targetTheta = 0,
        bool isRelativeToZero = true,
        double desiredValue = 10000,
        double errorLoopEndValue = 0.8,
        double turnErrorLoopEndValue = 2);

    /// @brief This method will turn the robot to a certain angle relative to the field
    /// @param targetTheta This is the angle at which you want the robot to turn to in degrees
    void Turn(double targetTheta, double turnErrorConstants[3], double errorValue = 1.2);

    /// @brief This method gets the robot to just drive straight, but it doesn't use a PID so it goes quite fast and is used for shorter distances that don't require a lot of accuracy
    /// @param drive_distance is how far you want the robot to drive
    /// @param speed is the speed at which you want the robot to drive
    /// @return Void
    void drive_straight(float drive_distance, float speed);
};

#endif