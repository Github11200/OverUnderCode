#include "vex.h"

using namespace vex;

/// @brief This controls intaking, outtaking, and retracting or extending the entire intake
int IntakeControl()
{
    while (true)
    {
        // If the up button is being pressed then extend the intake otherwise pull the intake back if the down button is being pressed
        if (Controller.ButtonUp.pressing())
            IntakePiston.set(true);
        else if (Controller.ButtonDown.pressing())
            IntakePiston.set(false);

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

        vex::task::sleep(25);
    }

    return 0;
}