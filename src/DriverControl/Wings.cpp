#include "../../include/DriverControl/Wings.h"

using namespace vex;

int Wings()
{
    // This stores the value for whether or not the wing is extended
    static bool wingsExtended = false;
    static bool rightWingExtended = false;
    static bool leftWingExtended = false;

    while (true)
    {
        // If the right arrow button is pressed then extend or retract the wings based on their current state
        if (Controller.ButtonL2.pressing())
        {
            wings.set(wingsExtended ? false : true);
            wingsExtended = wingsExtended ? false : true;

            wait(150, vex::timeUnits::msec);
        }

        vex::task::sleep(40);
    }
}