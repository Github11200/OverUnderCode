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

    Inertial.calibrate();
    wait(4.4, vex::timeUnits::sec);
    Controller.rumble(rumbleShort);
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
    /*==============================================
                    SKILLS SLOT 2
    ==============================================*/

    // Pop intake out
    IntakePiston.set(true);
    wait(1, vex::timeUnits::sec);
    IntakePiston.set(false);
    wait(0.8, vex::timeUnits::sec);
    IntakePiston.set(true);
    wait(1, vex::timeUnits::sec);
    IntakePiston.set(false);

    // Move the robot to the pipe for rapid firing
    pid.Turn(320, 0.22);
    pid.MoveToPoint(0, 0, 320, true, 16);
    pid.Turn(257);
    pid.drive_straight(16, 50);

    // Rapid fire the tri balls
    Catapult.setVelocity(100, vex::percentUnits::pct);
    Catapult.spinFor(vex::directionType::fwd, 39, vex::timeUnits::sec);

    // Curve the robot around to face the post, and get ready to go through it
    pid.drive_straight(-4, 100);
    wait(0.1, vex::timeUnits::sec);
    pid.MoveToPoint(0, 0, 95.4, true, 20, 0.211, 0.8, 2.4);
    wait(0.1, vex::timeUnits::sec);

    // Move the robot over to the other side
    pid.MoveToPoint(0, 0, 91, true, 35.5, 0.211, 0.8, 3);
    pid.MoveToPoint(0, 0, 84, true, 37.5, 0.211, 0.8, 2.6);

    // PUSH TRI BALLS INTO RIGHT SIDE OF GOAL
    Intake.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, 23, true, 21, 0.21, 1.39, 5.7);
    pid.Turn(13, 0.5, 2.3);
    pid.drive_straight(40, 90);
    pid.drive_straight(-30, 90);
    pid.drive_straight(30, 90);
    pid.MoveToPoint(0, 0, 13, true, -16.5, 0.22, 3.21, 7);

    // PUSH TRI BALLS INTO MIDDLE PART OF GOAL
    pid.Turn(317, 0.23);
    pid.MoveToPoint(0, 0, 317, true, 47, 0.211, 0.8, 2.3);
    wings.set(true);
    pid.MoveToPoint(0, 0, 83.5, true, 30, 0.25, 3.4, 7, 0.95);
    pid.drive_straight(20, 90);
    pid.drive_straight(-20, 90);
    pid.drive_straight(20, 90);
    wings.set(false);

    // Move the robot back and turn and move it to the next point
    pid.MoveToPoint(0, 0, 83.5, true, -23, 0.22, 0.8, 2.7);
    pid.Turn(30, 0.24);
    pid.MoveToPoint(0, 0, 30, true, 39);

    // PUSH TRI BALLS INTO LEFT PART OF GOAL
    Intake.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, 178, true, 48, 0.211, 0.8, 3.4);
    pid.drive_straight(15, 90);
    pid.drive_straight(-15, 90);
    pid.drive_straight(15, 90);

    /*==============================================
                    Match Auto SLOT 3
    ==============================================*/

    // // PUSH THE TRI BALL INTO THE LEFT SIDE OF THE GOAL
    // wings.set(true);
    // pid.drive_straight(25, 25);
    // pid.Turn(73, 0.25, 5.5);
    // wings.set(false);
    // pid.drive_straight(20, 35);
    // pid.Turn(76, 0.35, 7);
    // pid.drive_straight(17, 35);
    // Intake.spinFor(vex::directionType::rev, 1, vex::timeUnits::sec);
    // pid.drive_straight(14, 70);
    // pid.drive_straight(-10, 40);
    // pid.Turn(85, 0.5, 3);

    // wings.set(true);

    // // Move back and take the tri ball out of the corner
    // pid.MoveToPoint(0, 0, 65, true, -30, 0.23, 2, 7);
    // wings.set(false);
    // pid.MoveToPoint(0, 0, 180, true, 27, 0.23, 2, 5);
    // pid.drive_straight(15, 60);
    // wings.set(true);
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
    wings.set(false);

    // Initialize tasks
    task joysticks = task(JoystickControl);
    task buttons = task(Buttons);
    task wings = task(Wings);

    // User control code here, inside the loop
    while (1)
    {
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
