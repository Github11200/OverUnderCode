#include "../../include/DriverControl/ClimbingMechanism.h"

using namespace vex;

void ClampAndClimb()
{
    // If the driver presses the up button then keep on spinning the climbing motors under the driver lets go of the button
    if (Controller.ButtonUp.pressing())
    {
        while (Controller.ButtonUp.pressing())
            ClimbMotors.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        ClimbMotorLeft.stop(vex::brakeType::brake);
    }
}