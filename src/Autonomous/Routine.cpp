#include "../../include/Autonomous/Routine.h"

using namespace vex;
using namespace std;

PID pid;
double defaultErrorConstants[3] = {0.647, 0, 0.8};
double defaultTurnErrorConstants[3] = {0.2, 0, 0.15};

// double defaultTurnConstants[3] = {0.3, 0, 0.15};

void CalibrateInertial()
{
    Inertial.calibrate();
    while (Inertial.isCalibrating())
        wait(890, vex::timeUnits::msec);
    wait(800, vex::timeUnits::msec);
    Inertial.setHeading(0, vex::rotationUnits::deg);
    cout << "Is Done calibrating: " << Inertial.isCalibrating() << endl;
    Controller.rumble(rumbleShort);
}

void Skills()
{
    /*==============================================
                    SKILLS SLOT 3
    ==============================================*/
}

void FarSideAutonomous()
{
    /*==============================================
                        SLOT 2
    ==============================================*/

    // Intake the triball in front of the robot
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::rev, 1.2, vex::rotationUnits::rev, false);
    pid.drive_straight(7, 10);
    // pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 0, true, 2);

    // Move the robot back and line it up to take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 0, true, -32.5);
    double newTurnConstants[3] = {0.3, 0, 0.15};
    pid.Turn(326, newTurnConstants);

    // Take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 326, true, -15);
    newTurnConstants[0] = 0.29;
    pid.Turn(301, newTurnConstants);

    cout << "////////////////////////////////////////////" << endl;
    // Move back and turn to face the goal
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 301, true, -11);
    pid.Turn(276, newTurnConstants);

    // Push the tri balls in and move forward again
    pid.drive_straight(-9, 90);
    pid.drive_straight(9, 30);

    // Turn around and outtake the tri ball that was already inside the intake
    newTurnConstants[0] = 0.18;
    pid.Turn(91, newTurnConstants);
    Intake.spinFor(vex::directionType::rev, 1.1, vex::rotationUnits::rev, false);
    pid.drive_straight(11, 90);
    pid.drive_straight(-11, 30);

    // Turn to face the tri ball on the left, move forward, and intake it
    newTurnConstants[0] = 0.6;
    pid.Turn(18, newTurnConstants);
    Intake.spinFor(vex::directionType::rev, 4, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 18, true, 49);

    // Move the robot back, turn to face towards the goal, move forward, then outtake the tri ball pid.drive_straight(-2, 50);
    pid.Turn(143, defaultTurnErrorConstants);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 143, true, 12);
    Intake.setVelocity(70, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);

    // Turn, move forward and intake another tri ball
    newTurnConstants[0] = 0.215;
    pid.Turn(48, newTurnConstants);
    Intake.spinFor(vex::directionType::rev, 3, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 48, true, 16.5);

    // Move back, turn to face the goal, and outtake a second tri ball pid.drive_straight(-3, 50);
    pid.Turn(163, defaultTurnErrorConstants);
    Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);

    // // Turn so the back of the robot faces the goal, move the robot forward a bit, and then deploy the wings
    newTurnConstants[0] = 0.18;
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
                        SLOT 1
    ==============================================*/

    // Turn the robot, and move towards the goal
    double newTurnConstants[3] = {0.3, 0, 0.15};
    newTurnConstants[0] = 0.29;
    pid.Turn(45, newTurnConstants);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 45, true, 26);

    // Turn to face the goal, and outtake and push the tri ball into it
    newTurnConstants[0] = 0.34;
    pid.Turn(85, newTurnConstants);
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);
    pid.drive_straight(5.5, 90);

    // Move back again and align the robot to get ready to take the tri ball out of the corner
    pid.drive_straight(-5.5, 90);
    newTurnConstants[0] = 0.29;
    pid.Turn(62, newTurnConstants);

    // Move back and turn to take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 62, true, -18);
    wings.set(true);
    pid.Turn(27, defaultTurnErrorConstants);
    wings.set(false);

    // Move back and reset the position to 0
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 27, true, -14);
    newTurnConstants[0] = 0.28;
    pid.Turn(0, newTurnConstants);

    // Deploy the wings, and move back to touch the pole
    wings.set(true);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 0, true, -28);

    double newTurnConstants[3] = {0.3, 0, 0.15};
}
