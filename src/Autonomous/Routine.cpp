#include "../../include/Autonomous/Routine.h"

using namespace vex;
using namespace std;

PID pid;

void CalibrateInertial()
{
    Inertial.calibrate();
    while (Inertial.isCalibrating())
        wait(800, vex::timeUnits::msec);
    wait(800, vex::timeUnits::msec);
    Controller.rumble(rumbleShort);
}

void Skills()
{
    /*==============================================
                    SKILLS SLOT 3
    ==============================================*/

    // Move the robot to the pipe for rapid firing
    pid.Turn(320, 0.22);
    pid.MoveToPoint(0, 0, 320, true, 16);
    pid.Turn(257);
    pid.drive_straight(19, 38);

    // Rapid fire the tri balls
    CatapultRight.spin(vex::directionType::rev, 70, vex::percentUnits::pct);
    CatapultLeft.spin(vex::directionType::fwd, 70, vex::percentUnits::pct);
    wait(35, vex::timeUnits::sec);
    // Bring the catapult back into the down position
    while (CatapultRotation.position(vex::rotationUnits::deg) < 81)
    {
        CatapultRight.spin(vex::directionType::rev, 35, vex::percentUnits::pct);
        CatapultLeft.spin(vex::directionType::fwd, 35, vex::percentUnits::pct);
    }
    Catapult.stop(vex::brakeType::hold);

    // Curve the robot around to face the post, and get ready to go through it
    pid.drive_straight(-6, 100);
    wait(0.1, vex::timeUnits::sec);
    pid.MoveToPoint(0, 0, 95.4, true, 20, 0.23, 1, 4);
    wait(0.1, vex::timeUnits::sec);

    // Move the robot over to the other side
    pid.MoveToPoint(0, 0, 91, true, 35.5, 0.22, 2.6, 5.9, 0.89);
    pid.MoveToPoint(0, 0, 84, true, 37.5, 2, 3);

    // PUSH TRI BALLS INTO RIGHT SIDE OF GOAL
    Intake.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, 23, true, 21, 0.21, 2.39, 6.7);
    pid.Turn(13, 0.5, 4.3);
    pid.drive_straight(40, 90);
    pid.drive_straight(-30, 90);
    pid.drive_straight(30, 90);
    pid.MoveToPoint(0, 0, 13, true, -16.5, 0.22, 4.21, 7);

    // PUSH TRI BALLS INTO MIDDLE PART OF GOAL
    pid.Turn(317, 0.23, 3);
    pid.MoveToPoint(0, 0, 317, true, 47, 0.211, 8.5, 8.3);
    LeftWing.set(true);
    RightWing.set(true);
    pid.MoveToPoint(0, 0, 83.5, true, 30, 0.25, 8.4, 8, 0.95);
    pid.drive_straight(22, 90);
    pid.drive_straight(-22, 90);
    pid.drive_straight(20, 90);
    LeftWing.set(false);
    RightWing.set(false);

    // Move the robot back and turn and move it to the next point
    pid.MoveToPoint(0, 0, 83.5, true, -21, 0.22, 9, 10);
    pid.Turn(34, 0.24, 10);
    pid.MoveToPoint(0, 0, 30, true, 39, 0.23, 2, 5.7, 7.9);

    // PUSH TRI BALLS INTO LEFT PART OF GOAL
    Intake.spinFor(vex::directionType::rev, 1, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, 178, true, 48, 0.211, 4.8, 6.4);
    pid.drive_straight(15, 90);
    pid.drive_straight(-15, 90);
    pid.drive_straight(15, 90);
}

void FarSideAutonomous()
{
    /*==============================================
                        SLOT 2
    ==============================================*/

    // Extend the right wing and take the tri ball out of the corner
    LeftWing.set(true);
    wait(700, vex::timeUnits::msec);
    pid.Turn(9, 1.5, 3);
    pid.MoveToPoint(0, 0, 9, true, 23, 0.22, 0.9, 3.2, 0.84);
    // cout << "////////////////////////////////////////////////" << endl;

    // Turn towards the goal and pull the right wing back
    pid.Turn(70, 0.6, 3);
    wait(700, vex::timeUnits::msec);
    LeftWing.set(false);

    // Move forward a bit, start spinning the intake, and turn to face the goal
    pid.drive_straight(10, 70);
    wait(700, vex::timeUnits::msec);
    Intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    wait(1, vex::timeUnits::sec);

    Intake.stop(vex::brakeType::coast);
    pid.drive_straight(-13, 70);
    pid.Turn(9, 0.6, 3);
    pid.MoveToPoint(0, 0, 9, true, -24.5, 0.22, 0.9, 3.2, 0.84);

    pid.Turn(359, 0.3);
    pid.drive_straight(-40, 90);
}

void CloseSideAutonomous()
{
    /*==============================================
                        SLOT 1
    ==============================================*/

    // Extend the right wing and take the tri ball out of the corner
    wait(700, vex::timeUnits::msec);
    pid.Turn(353.5, 1.5, 3);
    pid.MoveToPoint(0, 0, 340, true, 23, 0.22, 0.9, 3.2, 0.84);
    // cout << "////////////////////////////////////////////////" << endl;

    // Turn towards the goal and pull the right wing back
    pid.Turn(305, 0.6, 3);
    wait(700, vex::timeUnits::msec);

    // Move forward a bit, start spinning the intake, and turn to face the goal
    pid.drive_straight(10, 80);
    wait(700, vex::timeUnits::msec);
    Intake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    wait(700, vex::timeUnits::msec);
    pid.Turn(330, 1.2, 12);
    wait(700, vex::timeUnits::msec);
    pid.drive_straight(3, 100);
    // cout << "TURN ONE ///////////////////////////////////////" << endl;

    // Push the tri ball in, move the robot back, and turn off the intake
    pid.drive_straight(-23, 60);
    Intake.stop(vex::brakeType::coast);
    wait(700, vex::timeUnits::msec);

    // Turn to have the catapult face the middle of the field and move backwards to the middle
    // position ending at 90 degrees
    pid.Turn(22, 0.35, 2);
    pid.drive_straight(-28, 70);
    pid.MoveToPoint(0, 0, 50, true, -33, 0.22, 1.2, 3.3);

    // Turn to the left, and push the tri balls over the pipe
    pid.Turn(130, 0.3);
    LeftWing.set(true);
    RightWing.set(true);
    wait(800, vex::timeUnits::msec);
    pid.drive_straight(-20, 80);
    pid.Turn(190, 0.3);
    pid.drive_straight(-56, 90);
    LeftWing.set(false);
    RightWing.set(false);
    pid.drive_straight(7, 80);
    pid.Turn(80);
    pid.drive_straight(54, 80);
    pid.MoveToPoint(0, 0, 165, true, 29, 0.22, 0.8, 3.5);
    // cout << "DONE //////////////////////////////////////////" << endl;
}