#include "../../include/Autonomous/PID.h"

using namespace vex;
using namespace std;

PID pid;
double defaultErrorConstants[3] = {0.647, 0, 0.8};
double defaultTurnErrorConstants[3] = {0.2, 0, 0.15};

double newTurnConstants[3] = {0.3, 0, 0.15};

// double defaultTurnConstants[3] = {0.3, 0, 0.15};

void CalibrateInertial()
{
    Inertial.calibrate();
    while (Inertial.isCalibrating())
        wait(895, vex::timeUnits::msec);
    wait(800, vex::timeUnits::msec);
    Inertial.setHeading(0, vex::rotationUnits::deg);
    cout << "Is calibrating: " << Inertial.isCalibrating() << endl;
    Controller.rumble(rumbleShort);
}

void Skills()
{
    /*==============================================
                    SKILLS SLOT 3
    ==============================================*/

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

void FarSideAutonomous()
{
    /*==============================================
                        SLOT 2
    ==============================================*/

    Blocker.spinFor(vex::directionType::rev, 0.7, vex::timeUnits::sec, 100, vex::velocityUnits::pct);

    // Intake the triball in front of the robot
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::rev, 1.2, vex::rotationUnits::rev, false);
    pid.drive_straight(7, 10);
    wait(0.7, vex::timeUnits::sec);

    // Move the robot back and line it up to take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 0, true, -32.5, 1.2, 2, 1);
    pid.Turn(326, newTurnConstants, 5);

    // Take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 326, true, -16);
    newTurnConstants[0] = 0.29;
    pid.Turn(301, newTurnConstants);

    // Move back and turn to face the goal
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 301, true, -11);
    pid.Turn(276, newTurnConstants);

    // Push the tri balls in and move forward again
    pid.drive_straight(-12, 90);
    pid.drive_straight(12, 30);

    // Turn around and outtake the tri ball that was already inside the intake
    newTurnConstants[0] = 0.19;
    pid.Turn(91, newTurnConstants, 2);
    wait(0.1, vex::timeUnits::sec);
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 1.3, vex::rotationUnits::rev, false);
    pid.drive_straight(11, 90);
    pid.drive_straight(-14, 30);
    wait(0.1, vex::timeUnits::sec);

    // Turn to face the tri ball on the left, move forward, and intake it
    newTurnConstants[0] = 0.3;
    pid.Turn(20, newTurnConstants);
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::rev, 6, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 20, true, 49, 2.4);
    wait(0.1, vex::timeUnits::sec);

    // Move the robot back, turn to face towards the goal, move forward, then outtake the tri ball pid.drive_straight(-2, 50);
    pid.Turn(143, defaultTurnErrorConstants, 3);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 143, true, 28);
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);
    pid.drive_straight(10, 80);
    pid.drive_straight(-23, 80);
    wait(0.1, vex::timeUnits::sec);

    // Turn, move forward and intake another tri ball
    newTurnConstants[0] = 0.35;
    pid.Turn(96, newTurnConstants);
    Intake.spinFor(vex::directionType::rev, 3, vex::rotationUnits::rev, false);
    pid.drive_straight(15, 20);
    wait(0.1, vex::timeUnits::sec);

    // Get the second tri ball and outtake
    newTurnConstants[0] = 0.32;
    pid.Turn(170, newTurnConstants, 2);
    Intake.spinFor(vex::directionType::fwd, 2, vex::rotationUnits::rev, false);
    pid.drive_straight(20, 70);
    wait(0.3, vex::timeUnits::sec);

    pid.drive_straight(-15, 40);
    newTurnConstants[0] = 0.3;
    wait(0.3, vex::timeUnits::sec);
    pid.Turn(30, newTurnConstants, 4);
    Intake.spinFor(vex::directionType::rev, 2, vex::rotationUnits::rev, false);
    wait(0.2, vex::timeUnits::sec);
    pid.drive_straight(10, 70);

    newTurnConstants[0] = 0.32;
    pid.Turn(170, newTurnConstants, 2);
    pid.drive_straight(25, 80);

    pid.drive_straight(-10, 30);

    // Move back, turn to face the goal, and outtake a second tri ball pid.drive_straight(-3, 50);
    pid.Turn(163, defaultTurnErrorConstants);
    Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);

    // Turn so the back of the robot faces the goal, move the robot forward a bit, and then deploy the wings
    newTurnConstants[0] = 0.17;
    pid.Turn(353, newTurnConstants);
    pid.drive_straight(2, 50);
    wings.set(true);

    // Move the robot back, push in the tri balls, and get the wings up
    pid.drive_straight(-22.5, 80);
    wings.set(false);

    // Move back, turn, move back again, and turn a bit more to touch the pipe
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 353, true, 26);
    pid.Turn(93, defaultTurnErrorConstants);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 93, true, -25.8);
    newTurnConstants[0] = 0.65;
    pid.Turn(87, newTurnConstants);
}

void CloseSideAutonomous()
{
    /*==============================================
                        SLOT 3
    ==============================================*/

    Blocker.spinFor(vex::directionType::rev, 0.7, vex::timeUnits::sec, 100, vex::velocityUnits::pct);
    //  Turn the robot, and move towards the goal
    newTurnConstants[0] = 0.24;
    pid.Turn(45, newTurnConstants);
    wait(0.2, vex::timeUnits::sec);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 45, true, 36);
    wait(0.2, vex::timeUnits::sec);

    // Turn to face the goal, and outtake and push the tri ball into it
    newTurnConstants[0] = 0.325;
    pid.Turn(80, newTurnConstants);
    Intake.setVelocity(95, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 2, vex::rotationUnits::rev, false);
    pid.drive_straight(7, 90);

    // Move back again and align the robot to get ready to take the tri ball out of the corner
    pid.drive_straight(-7, 90);
    newTurnConstants[0] = 0.29;
    pid.Turn(62, newTurnConstants);

    // Move back and turn to take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 58, true, -14);
    wings.set(true);
    pid.drive_straight(-13, 90);
    wait(0.6, vex::timeUnits::sec);
    // pid.Turn(27, defaultTurnErrorConstants);
    wings.set(false);
    pid.drive_straight(-5, 30);

    // Move back and reset the position to 0
    // pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 27, true, -14);
    newTurnConstants[0] = 0.28;
    pid.Turn(3, newTurnConstants);

    // // Deploy the wings, and move back to touch the pole
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 3, true, -37);
    wings.set(true);
}
