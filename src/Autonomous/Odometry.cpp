// #include "../../include/Autonomous/Odometry.h"

// using namespace std;
// using namespace vex;

// long double x = NULL;
// long double y = NULL;
// double theta = NULL;

// Odometry::Odometry(int startingPosition)
// {
//     /*
//         ADD IN A SWITCH STATEMENT TO SET THE X AND Y POSITION OF THE ROBOT IN THIS CLASS
//         BASED ON WHERE IT IS STARTING.
//     */
// }

// void Odometry::UpdateEncoders()
// {
//     // Update the values of the current encoder positions by getting the average of 2 motors on each side of the robot
//     this->currentBackEncoders = BackEncoder.position(vex::rotationUnits::deg);
//     this->currentRightEncoders = RightEncoder.position(vex::rotationUnits::deg);

//     // Calculate the distance traveled by each side of the chassis
//     this->backEncoderDistanceTraveled = ((currentBackEncoders - previousBackEncoders) * (wheelDiameter * M_PI)) / 360;
//     this->rightEncoderDistanceTraveled = ((currentRightEncoders - previousRightEncoders) * (wheelDiameter * M_PI)) / 360;

//     // Make the previous encoder values to the current one
//     this->previousBackEncoders = this->currentBackEncoders;
//     this->previousRightEncoders = this->currentRightEncoders;
// }

// void Odometry::UpdateTheta()
// {
//     this->previousTheta = theta;
//     theta = Inertial.pitch(vex::rotationUnits::deg);
//     this->changeInTheta = theta - this->previousTheta;
// }

// void Odometry::UpdatePosition()
// {
//     // Calculate how much the robot has moved on the x and y
//     this->xIncrement = (2 * sin(Inertial.heading(vex::rotationUnits::deg) / 2)) * ((this->backEncoderDistanceTraveled / this->changeInTheta) + this->tB);
//     this->yIncrement = (2 * sin(Inertial.heading(vex::rotationUnits::deg) / 2)) * ((this->rightEncoderDistanceTraveled / this->changeInTheta) + this->tR);

//     // Increment the x and y positions by the computed value
//     x += this->xIncrement;
//     y += this->yIncrement;
// }