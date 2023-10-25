#include "../../include/DriverControl/JoystickControl.h"

using namespace vex;

int JoystickControl()
{
    // Get the power and turn from the controller joysticks, and set the deadzone to 5 (this reduces controller drift)
    double power = 0;
    double turn = 0;
    float deadZone = 5;

    // Run this as a task until the entire program stops
    while (true)
    {
        // Update the power and turn again
        power = -Controller.Axis1.position();
        turn = Controller.Axis3.position();

        // If the power is within the deadzone then calculate it
        if (power > deadZone || power < -deadZone)
            power > 0 ? power = pow(power, 2) * 0.01 : power = -(pow(power, 2) * 0.01);

        // If the turn is within the deadzone then calculate it
        if (turn > deadZone || turn < -deadZone)
            turn > 0 ? turn = pow(turn, 2) * 0.01 : turn = -(pow(turn, 2) * 0.01);

        // Spin the motors based on the power and turn
        Left.spin(vex::forward, power - turn, vex::percentUnits::pct);
        Right.spin(vex::forward, power + turn, vex::percentUnits::pct);

        vex::task::sleep(25);
    }

    return 0;
}