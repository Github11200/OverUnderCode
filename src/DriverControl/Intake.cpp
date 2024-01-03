#include "../../include/DriverControl/Intake.h"

using namespace vex;

void IntakeControl()
{
    // While the R1 or R2 button's are being pressed either make the intake intake or outtake depending on which button is pressed
    while (Controller.ButtonR1.pressing() || Controller.ButtonR2.pressing())
    {
        if (Controller.ButtonR1.pressing())
            Intake.spin(vex::directionType::rev, 90, vex::percentUnits::pct);
        else if (Controller.ButtonR2.pressing())
            Intake.spin(vex::directionType::fwd, 100, vex::percentUnits::pct);
    }

    // Always set the intake to a brake type of coast
    Intake.stop(vex::brakeType::coast);
}