#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "vex.h"

#pragma once
extern long double x;
extern long double y;
extern double theta;

/**
 * @brief This class handles updating the position and orientation of the robot for the autonomous
 *
 */
class Odometry
{
private:
    // Constants
    float wheelDiameter = 4.2;

    // Orientation
    long double changeInTheta = 0;
    long double previousTheta = 0;

    // Current encoder values
    double currentLeftEncoders = 0;
    double currentRightEncoders = 0;

    // Previous encoder values
    double previousLeftEncoders = 0;
    double previousRightEncoders = 0;

    // Encoder distances
    double leftEncoderDistanceTraveled = 0;
    double rightEncoderDistanceTraveled = 0;

    // Variables for storing the amount that the x and y coordinates have incremented by from the previous loop
    long double xIncrement = 0;
    long double yIncrement = 0;

    // This is the average distance from the two sides of the chassis
    long double distanceTraveledByEncodersAverage = 0;

public:
    long double previousX = 0;
    long double previousY = 0;

    Odometry(int startingPosition);

    /// @brief This method calculates how much each encoder has moved based on the previous and current values into inches
    void UpdateEncoders();

    /// @brief This method gets the current angle of the robot on the field and updates the previous and change in theta properties
    void UpdateTheta();

    /// @brief This method gets the current x and y position of the robot on the field
    void UpdatePosition();
};

#endif