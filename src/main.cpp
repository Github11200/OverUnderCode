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
#include "../include/Autonomous/Odometry.h"
#include "../include/Autonomous/PID.h"
#include "../include/Autonomous/PurePursuit.h"
// #include "../include/Autonomous/DriverAutonomous.h"

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
CatapultHandler catapultHandler;
// DriverAutonomous driverAutonomous(&catapultHandler);

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

    // Calibrate all of the sensors
    // RightEncoder.setPosition(0, vex::rotationUnits::deg);
    // BackEncoder.setPosition(0, vex::rotationUnits::deg);

    // Inertial.calibrate();
    // wait(4.4, vex::timeUnits::sec);
    // Controller.rumble(rumbleShort);
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

    // // Pop intake out
    // IntakePiston.set(true);
    // wait(1, vex::timeUnits::sec);
    // IntakePiston.set(false);

    // // Move the robot to the pipe for rapid firing
    // pid.Turn(320, 0.22);
    // pid.MoveToPoint(0, 0, 320, true, 16);
    // pid.Turn(257);
    // pid.drive_straight(19, 38);

    // // Rapid fire the tri balls
    // Catapult.setVelocity(100, vex::percentUnits::pct);
    // Catapult.spinFor(vex::directionType::fwd, 39, vex::timeUnits::sec);

    // // Curve the robot around to face the post, and get ready to go through it
    // pid.drive_straight(-6, 100);
    // wait(0.1, vex::timeUnits::sec);
    // pid.MoveToPoint(0, 0, 95.4, true, 20, 0.23, 1, 4);
    // wait(0.1, vex::timeUnits::sec);

    // // Move the robot over to the other side
    // pid.MoveToPoint(0, 0, 91, true, 35.5, 0.22, 2.6, 5.9, 0.89);
    // pid.MoveToPoint(0, 0, 84, true, 37.5, 2, 3);

    // // PUSH TRI BALLS INTO RIGHT SIDE OF GOAL
    // Intake.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, false);
    // pid.MoveToPoint(0, 0, 23, true, 21, 0.21, 2.39, 6.7);
    // pid.Turn(13, 0.5, 4.3);
    // pid.drive_straight(40, 90);
    // pid.drive_straight(-30, 90);
    // pid.drive_straight(30, 90);
    // pid.MoveToPoint(0, 0, 13, true, -16.5, 0.22, 4.21, 7);

    // // PUSH TRI BALLS INTO MIDDLE PART OF GOAL
    // pid.Turn(317, 0.23, 3);
    // pid.MoveToPoint(0, 0, 317, true, 47, 0.211, 8.5, 8.3);
    // wings.set(true);
    // pid.MoveToPoint(0, 0, 83.5, true, 30, 0.25, 8.4, 8, 0.95);
    // pid.drive_straight(22, 90);
    // pid.drive_straight(-22, 90);
    // pid.drive_straight(20, 90);
    // wings.set(false);

    // // Move the robot back and turn and move it to the next point
    // pid.MoveToPoint(0, 0, 83.5, true, -21, 0.22, 9, 10);
    // pid.Turn(34, 0.24, 10);
    // pid.MoveToPoint(0, 0, 30, true, 39, 0.23, 2, 5.7, 7.9);

    // // PUSH TRI BALLS INTO LEFT PART OF GOAL
    // Intake.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, false);
    // pid.MoveToPoint(0, 0, 178, true, 48, 0.211, 4.8, 6.4);
    // pid.drive_straight(15, 90);
    // pid.drive_straight(-15, 90);
    // pid.drive_straight(15, 90);

    /*==============================================
                Match Auto SLOT 3
    ==============================================*/

    // PUSH THE TRI BALL INTO THE LEFT SIDE OF THE GOAL
    pid.drive_straight(17, 25);
    pid.MoveToPoint(0, 0, 270, true, 26, 0.29);
    Intake.spinFor(vex::directionType::rev, 2, vex::rotationUnits::rev, false);
    pid.drive_straight(5, 60);
    pid.drive_straight(-10, 80);
    pid.Turn(285, 0.9, 6);
    pid.drive_straight(10, 60);
    pid.drive_straight(-15, 80);
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
        catapultHandler.buttons();

        vex::task::sleep(20);
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
    // LeftWing.set(false);
    // RightWing.set(false);

    // Initialize tasks
    // task joysticks = task(JoystickControl);
    // task buttons = task(Buttons);
    // task wings = task(Wings);

    // Calibrate the inertial
    Inertial.calibrate();
    wait(5, vex::timeUnits::sec);
    Controller.rumble(rumbleShort);

    // Extend the right wing and take the tri ball out of the corner
    RightWing.set(true);
    wait(700, vex::timeUnits::msec);
    pid.Turn(353.5, 1.5, 3);
    pid.MoveToPoint(0, 0, 353.5, true, 23, 0.22, 0.9, 3.2, 0.84);
    cout << "////////////////////////////////////////////////" << endl;

    // Turn towards the goal and pull the right wing back
    pid.Turn(300, 0.6, 3);
    wait(700, vex::timeUnits::msec);
    RightWing.set(false);

    // Move forward a bit, start spinning the intake, and turn to face the goal
    pid.drive_straight(9, 70);
    wait(700, vex::timeUnits::msec);
    Intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    wait(700, vex::timeUnits::msec);
    pid.Turn(260, 1.2, 12);
    wait(700, vex::timeUnits::msec);
    cout << "TURN ONE ///////////////////////////////////////" << endl;

    // Push the tri ball in, move the robot back, and turn off the intake
    pid.drive_straight(8, 90);
    pid.drive_straight(-26, 60);
    Intake.stop(vex::brakeType::coast);
    wait(700, vex::timeUnits::msec);

    // Turn to have the catapult face the middle of the field and move backwards to the middle
    // position ending at 90 degrees
    pid.Turn(30);
    pid.drive_straight(-20, 70);
    pid.MoveToPoint(0, 0, 90, true, -36, 0.22, 1.2, 3);

    // Turn to the left, and push the tri balls over the pipe
    pid.Turn(15, 0.3);
    LeftWing.set(true);
    RightWing.set(true);
    pid.drive_straight(-43, 100);

    // Move forward a bit, turn to the right, drive straight, and then curve
    // around the pipe to face the front
    pid.drive_straight(10, 60);
    pid.Turn(45, 0.3);
    pid.drive_straight(60, 80);
    pid.MoveToPoint(0, 0, 180, true, 33);
    pid.drive_straight(30, 70);
    cout
        << "DONE //////////////////////////////////////////" << endl;

    // pid.MoveToPoint(0, 0, 320, true, 27);
    // cout << "done" << endl;
    // RightWing.set(false);
    // pid.MoveToPoint(0, 0, 270, true, 30);

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
