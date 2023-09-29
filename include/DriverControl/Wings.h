#include "vex.h"

using namespace vex;

/// @brief This function controls both of the wings on the robot
int Wings()
{
    // This stores the value for which wing is open and which one is not
    bool rightWingValue = false;
    bool leftWingValue = true;

    while (true)
    {
        // If the x button is pressed then change the right wing to the opposite value of what it is, the same goes for the left wing abd b button
        if (Controller.ButtonX.pressing())
            RightWing.set(!rightWingValue);
        else if (Controller.ButtonB.pressing())
            LeftWing.set(!leftWingValue);
    }

    return 0;
}