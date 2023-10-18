#include "vex.h"

using namespace vex;

/// @brief This function controls both of the wings on the robot
int Wings()
{
    // This stores the value for whether or not the wing is extended
    static bool wingsExtended = false;

    while (true)
    {
        // If the x button is pressed then extend or retract the wings based on their current state
        if (Controller.ButtonX.pressing())
        {
            wings.set(wingsExtended ? false : true);
            wingsExtended = wingsExtended ? false : true;
            wait(600, vex::timeUnits::msec);
        }

        vex::task::sleep(100);
    }
}