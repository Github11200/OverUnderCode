#include "vex.h"

using namespace vex;

/// @brief This function controls both of the wings on the robot
void Wings()
{
    // This stores the value for whether or not the wing is extended
    bool wingsExtended = false;

    // If the x button is pressed then extend or retract the wings based on their current state
    if (Controller.ButtonX.pressing())
        wings.set(!wingsExtended);
}