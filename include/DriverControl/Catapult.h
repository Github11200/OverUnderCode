#include "vex.h"

using namespace vex;

/// @brief Rewinds and shoots the catapult based on where it is and the input from the controller
int CatapultButtons()
{
    bool isCatapultDown = true;

    while (true)
    {
        // THE L1 BUTTON IS FOR SINGLE CATAPULT FIRE
        if (Controller.ButtonL1.pressing())
        {
            // If the catapult is down then spin the motor in reverse for 1 second to shoot it
            if (isCatapultDown)
            {
                Catapult.spinFor(vex::directionType::rev, 1, vex::timeUnits::sec);
                isCatapultDown = false;
            }
        }
        else if (Controller.ButtonL2.pressing()) // THE L2 BUTTON IS FOR RAPID FIRE
        {
            // Wait for the driver to let go of the L2 button
            if (!Controller.ButtonL2.pressing())
            {
                // While the user doesn't press the l2 button again, continue spinning the catapult
                while (!Controller.ButtonL2.pressing())
                    Catapult.spin(vex::directionType::rev, 100, vex::percentUnits::pct);
            }
        }

        // Bring the catapult back into the down position
        while (CatapultRotationSensor.position(vex::rotationUnits::deg) > 0)
            Catapult.spin(vex::directionType::rev, 100, vex::percentUnits::pct);

        Catapult.stop(vex::brakeType::hold);
        isCatapultDown = true;

        vex::task::sleep(25);
    }

    return 0;
}