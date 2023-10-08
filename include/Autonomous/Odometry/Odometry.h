#include "vex.h"
#include "math.h"
#include "string"

using namespace std;
using namespace vex;

#pragma once
extern long double x = 0;
extern long double y = 0;
extern double theta = 0;

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

    /// @brief This method calculates how much each encoder has moved based on the previous and current values into inches
    void UpdateEncoders()
    {
        // Update the values of the current encoder positions by getting the average of 2 motors on each side of the robot
        this->currentLeftEncoders = (FrontLeft.position(vex::rotationUnits::deg) + BackLeft.position(vex::rotationUnits::deg)) / 2;
        this->currentRightEncoders = (FrontRight.position(vex::rotationUnits::deg) + BackRight.position(vex::rotationUnits::deg)) / 2;

        // Calculate the distance traveled by each side of the chassis
        this->leftEncoderDistanceTraveled = ((currentLeftEncoders - previousLeftEncoders) * (wheelDiameter * M_PI)) / 360;
        this->rightEncoderDistanceTraveled = ((currentRightEncoders - previousRightEncoders) * (wheelDiameter * M_PI)) / 360;

        // Make the previous encoder values to the current one
        this->previousLeftEncoders = this->currentLeftEncoders;
        this->previousRightEncoders = this->currentRightEncoders;
    }

    /// @brief This method gets the current angle of the robot on the field and updates the previous and change in theta properties
    void UpdateTheta()
    {
        this->previousTheta = theta;
        theta = Inertial.pitch(vex::rotationUnits::deg);
        this->changeInTheta = theta - this->previousTheta;
    }

    /// @brief This method gets the current x and y position of the robot on the field
    void UpdatePosition()
    {
        // Update the orientation
        this->UpdateTheta();

        this->distanceTraveledByEncodersAverage = (this->leftEncoderDistanceTraveled + this->rightEncoderDistanceTraveled) / 2;

        // Calculate how much the robot has moved on the x and y
        this->xIncrement = this->distanceTraveledByEncodersAverage * cos(theta);
        this->yIncrement = this->distanceTraveledByEncodersAverage * sin(theta);

        // Increment the x and y positions by the computed value
        x += this->xIncrement;
        y += this->yIncrement;
    }

    Odometry(string fieldPosition)
    {
        /*
            ADD IN A SWITCH STATEMENT TO SET THE X AND Y POSITION OF THE ROBOT IN THIS CLASS
            BASED ON WHERE IT IS STARTING.
        */
    }

    ~Odometry()
    {
    }
};