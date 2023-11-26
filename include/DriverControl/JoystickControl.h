#ifndef JOYSTICKCONTROL_H
#define JOYSTICKCONTROL_H

#include "vex.h"

/// @brief This method finds the minimum angle that the robot has to turn in order to face the target angle
/// @param targetAngle This is the angle at which we want the robot to be at
/// @param currentHeading This is the angle at which the robot is currently at
/// @return The minimum number of degrees the robot has to turn to reach the target angle
double findMinAngle(double targetAngle, double currentHeading);

/// @brief This function returns 1 or -1 based on whether the input number is positive or negative
/// @param num The number who's sign you want to figure out
/// @return 1 or -1 based on whether the input number is positive or negative
int sgn(double num);

/// @brief Controls the drivetrain speed based on the joystick inputs
/// @return 0
int JoystickControl();

#endif