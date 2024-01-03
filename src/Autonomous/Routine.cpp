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
}

void CloseSideAutonomous()
{
    /*==============================================
                        SLOT 1
    ==============================================*/
}