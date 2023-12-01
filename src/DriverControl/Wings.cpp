#include "../../include/DriverControl/Wings.h"

using namespace vex;

int Wings()
{
    // This stores the value for whether or not the wing is extended
    static bool rightWingExtended = false;
    static bool leftWingExtended = false;

    while (true)
    {
        // If the right arrow button is pressed then extend or retract the wings based on their current state
        if (Controller.ButtonLeft.pressing())
        {
            RightWing.set(rightWingExtended ? false : true);
            rightWingExtended = rightWingExtended ? false : true;
            wait(150, vex::timeUnits::msec);
        }
        else if (Controller.ButtonRight.pressing())
        {
            LeftWing.set(leftWingExtended ? false : true);
            leftWingExtended = leftWingExtended ? false : true;
            wait(150, vex::timeUnits::msec);
        }
        else if (Controller.ButtonDown.pressing())
        {
            RightWing.set(rightWingExtended ? false : true);
            LeftWing.set(leftWingExtended ? false : true);

            rightWingExtended = rightWingExtended ? false : true;
            leftWingExtended = leftWingExtended ? false : true;

            wait(150, vex::timeUnits::msec);
        }

        vex::task::sleep(40);
    }
}