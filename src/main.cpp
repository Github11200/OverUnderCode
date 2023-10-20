/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       patel                                                     */
/*    Created:      8/22/2023, 9:55:52 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

// Include the autonomous files
#include "../include/Autonomous/Odometry/Odometry.h"
#include "../include/Autonomous/PID/PID.h"
#include "../include/Autonomous/PurePursuit/PurePursuit.h"
#include "../include/Autonomous/DriverAuto/DriverAutonomous.h"

// Include the driver control files
#include "../include/DriverControl/JoystickControl.h"
#include "../include/DriverControl/Catapult.h"
#include "../include/DriverControl/Intake.h"
#include "../include/DriverControl/Wings.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// Global variables
PID pid;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{
    // All activities that occur before the competition starts
    // Example: clearing encoders, setting servo positions, ...

    CatapultButtons(); // Bring the catapult down

    // Calibrate all of the sensors
    CatapultRotationSensor.setPosition(0, vex::rotationUnits::deg);
    // Inertial.calibrate();
    // wait(4, vex::timeUnits::sec);

    // Let the user know that the inertial is calibrated by rumbling the controller and filling the brain with a green rectangle
    // Controller.rumble(rumbleShort);
    Brain.Screen.setFillColor(vex::color::green);
    Brain.Screen.drawRectangle(1, 1, 48, 12);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/// @brief This function calls the method in the odometry class to update the robot position and orientation
/// @return 0
// int callOdometryMethod()
// {
//     while (true)
//     {
//         odometry.UpdatePosition();
//         vex::task::sleep(10);
//     }

//     return 0;
// }

void autonomous(void)
{
    // ..........................................................................
    // Insert autonomous user code here.
    // ..........................................................................
    // pid.drive_straight(2, 50);
    // pid.Turn(315);
    // pid.MoveToPoint(0, 0, 0, true, 15.963379363045494);
    // pid.Turn(40);
    // pid.drive_straight(-4, 40);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/// @brief This function handles all of the button inputs
/// @return 0
int Buttons()
{
    while (true)
    {
        IntakeControl();
        CatapultButtons();

        vex::task::sleep(15);
    }

    return 0;
}

/// @brief This function calls the record method to record buttons and joystick controls
/// @return 0
// int RecordDriver()
// {
//     while (true)
//     {
//         driverAutonomous.record();
//         vex::task::sleep(10);
//     }

//     return 0;
// }

void usercontrol(void)
{
    CatapultRotationSensor.setPosition(0, vex::rotationUnits::deg);

    // Initialize tasks
    // task joysticks = task(JoystickControl);
    // task buttons = task(Buttons);
    // task wings = task(Wings);

    Inertial.calibrate();
    wait(4.35, vex::timeUnits::sec);

    // Move the robot to the pipe for rapid firing
    pid.Turn(320, 0.22);
    cout << "DONE TURN////////////////////////////////" << endl;
    pid.MoveToPoint(0, 0, 320, true, 16);
    pid.Turn(257);
    pid.drive_straight(15.7, 50);

    wait(1, vex::timeUnits::sec);

    // Curve the robot around to face the post, and get ready to go through it
    pid.drive_straight(-4, 100);
    wait(0.1, vex::timeUnits::sec);
    pid.MoveToPoint(0, 0, 93.2, true, 20);
    wait(0.1, vex::timeUnits::sec);
    cout << "DONE CURVE////////////////////////////////" << endl;

    // Move the robot over to the other side
    pid.MoveToPoint(0, 0, 90, true, 35.5);
    pid.MoveToPoint(0, 0, 96, true, 37, 0.28);

    cout << "ONTO THE OTHER SIDE//////////////////////" << endl;

    // Turn and push the tri balls into the side of the goal
    pid.MoveToPoint(0, 0, 21, true, 21, 0.21, 1.39, 5.7);
    cout << "IN FRONT OF GOAL//////////////////////////////////////" << endl;
    pid.Turn(13, 0.5, 2.3);
    cout << "DONE TURN/////////////////////////////////////////////////" << endl;
    pid.drive_straight(30, 90);
    pid.MoveToPoint(0, 0, 13, true, -20, 0.211, 3.21, 2.3);
    cout << "DONE PUSHING IN TRI BALLS/////////////////////////////////////////" << endl;

    pid.Turn(326, 0.22);
    pid.MoveToPoint(0, 0, 326, true, 59.5, 0.211, 0.8, 2.3);
    pid.Turn(85);
    pid.MoveToPoint(0, 0, 85, true, 24);

    // User control code here, inside the loop
    while (1)
    {
        // cout << "inertial heading: " << Inertial.heading(deg) << endl;
        // This is the main execution loop for the user control program.
        // Each time through the loop your program should update motor + servo
        // values based on feedback from the joysticks.

        // ........................................................................
        // Insert user code here. This is  where you use the joystick values to
        // update your motors, etc.
        // ............ ............................................................

        wait(20, msec); // Sleep the task for a short amount of time to
                        // prevent wasted resources.
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        wait(100, msec);
    }
}
