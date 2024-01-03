#include "../../include/Autonomous/Routine.h"

using namespace vex;
using namespace std;

PID pid;
double defaultErrorConstants[3] = {0.22, 0.22, 0.22};
double defaultTurnErrorConstants[3] = {0.8, 0.8, 0.8};

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
}

void FarSideAutonomous()
{
    /*==============================================
                        SLOT 2
    ==============================================*/

    // Intake the triball in front of the robot
    Intake.spinFor(vex::directionType::rev, 2, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 0, true, 3.5);

    // Move the robot back and line it up to take the tri ball out of the corner
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 0, true, -32.5);
    pid.Turn(326, defaultTurnErrorConstants);

    // Take the tri ball out of the corner
    wings.set(true);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 327, true, -15);
    pid.Turn(301, defaultTurnErrorConstants);
    wings.set(false);

    // Move back and turn to face the goal
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 301, true, -11);
    pid.Turn(276, defaultTurnErrorConstants);

    // Push the tri balls in and move forward again
    pid.drive_straight(-9, 90);
    pid.drive_straight(9, 60);

    // Turn around and outtake the tri ball that was already inside the intake
    pid.Turn(91, defaultTurnErrorConstants);
    Intake.spinFor(vex::directionType::rev, 1.1, vex::rotationUnits::rev, false);
    pid.drive_straight(11, 90);
    pid.drive_straight(-11, 60);

    // Turn to face the tri ball on the left, move forward, and intake it
    pid.Turn(18, defaultTurnErrorConstants);
    Intake.spinFor(vex::directionType::rev, 4, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 18, true, 49);

    // Move the robot back, turn to face towards the goal, move forward, then outtake the tri ball
    pid.drive_straight(-2, 50);
    pid.Turn(143, defaultTurnErrorConstants);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 143, true, 12);
    Intake.setVelocity(70, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);

    // Turn, move forward and intake another tri ball
    pid.Turn(48, defaultTurnErrorConstants);
    Intake.spinFor(vex::directionType::rev, 3, vex::rotationUnits::rev, false);
    pid.MoveToPoint(0, 0, defaultErrorConstants, defaultTurnErrorConstants, 48, true, 16.5);

    pid.drive_straight(-3, 50);
}

void CloseSideAutonomous()
{
    /*==============================================
                        SLOT 1
    ==============================================*/
}