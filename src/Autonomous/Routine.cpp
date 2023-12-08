#include "../../include/Autonomous/Routine.h"

using namespace vex;
using namespace std;

PID pid;

void CalibrateInertial() {
    Inertial.calibrate();
    while (Inertial.isCalibrating())
        wait(200, vex::timeUnits::msec);
    Controller.rumble(rumbleShort);
}

void Skills() {
    /*==============================================
                    SKILLS SLOT 3
    ==============================================*/

    // Move the robot to the pipe for rapid firing
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
}

void FarSideAutonomous() {
    /*==============================================
                        SLOT 2
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

void CloseSideAutonomous() {
    /*==============================================
                        SLOT 1
    ==============================================*/

    // TEST CODE
    pid.Turn(270);
    pid.MoveToPoint(0, 0, 270, true, 30);

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
}