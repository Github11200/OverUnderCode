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
// #include "../include/Autonomous/Odometry.h"
// #include "../include/Autonomous/PurePursuit.h"
#include "../include/Autonomous/Routine.h"
// #include "../include/Autonomous/DriverAutonomous.h"

// Include the driver control files
#include "../include/DriverControl/JoystickControl.h"
#include "../include/DriverControl/Catapult.h"
#include "../include/DriverControl/Intake.h"
#include "../include/DriverControl/Wings.h"
#include "../include/DriverControl/Blocker.h"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// Global variables
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

    // CatapultRotation.setPosition(0, vex::rotationUnits::deg);
    // CalibrateInertial();
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

    // Slot 1
    // CloseSideAutonomous();

    // Slot 2
    // FarSideAutonomous();

    // Slot 3
    // Skills();
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

        if (Controller.ButtonUp.pressing())
        {
            deploy();
            wait(500, vex::timeUnits::msec);
        }

        if (Controller.ButtonDown.pressing())
        {
            rewindBlocker();
            wait(500, vex::timeUnits::msec);
        }

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
//         vex::task::sleep(40);
//     }

//     return 0;
// }

void usercontrol(void)
{
    // CatapultRotation.setPosition(0, vex::rotationUnits::deg);
    // LeftWing.set(false);
    // RightWing.set(false);

    wings.set(false);

    CalibrateInertial();

    // FarSideAutonomous();
    // PID pid;

    Skills();

    // double errorConstants[3] = {0.647, 0, 0.8};
    // double turnErrorConstants[3] = {0.2, 0, 0.15};

    // double customTurnConstants[3] = {0.6, 0, 0.15};
    // pid.Turn(6, customTurnConstants);
    // cout << "Inertial Heading: " << Inertial.heading(vex::rotationUnits::deg) << endl;

    // Initialize tasks
    // task joysticks = task(JoystickControl);
    // task buttons = task(Buttons);
    // task wings = task(Wings);

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
