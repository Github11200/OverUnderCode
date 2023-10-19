#include "vex.h"

using namespace vex;

/// @brief This controls intaking, outtaking, and retracting or extending the entire intake
void IntakeControl()
{
    // If the up button is being pressed then extend the intake
    if (Controller.ButtonUp.pressing())
    {
        IntakePiston.set(false);
        wait(1, vex::timeUnits::sec);
        IntakePiston.set(true);
    }

    // While the R1 or R2 button's are being pressed either make the intake intake or outtake depending on which button is pressed
    while (Controller.ButtonR1.pressing() || Controller.ButtonR2.pressing())
    {
        if (Controller.ButtonR1.pressing())
            Intake.spin(vex::directionType::fwd, 100, vex::percentUnits::pct);
        else if (Controller.ButtonR2.pressing())
            Intake.spin(vex::directionType::rev, 100, vex::percentUnits::pct);
    }

    // Always set the intake to a brake type of coast
    Intake.stop(vex::brakeType::coast);
}