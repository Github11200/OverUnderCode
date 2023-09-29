#include "vex.h"

using namespace vex;

/// @brief Controls the drivetrain speed based on the joystick inputs
/// @return 0
int JoystickControl()
{
    // Get the power and turn from the controller joysticks, and set the deadzone to 5 (this reduces controller drift)
    double power = Controller.Axis3.position();
    double turn = Controller.Axis1.position();
    float deadZone = 5;

    // Run this as a task until the entire program stops
    while (true)
    {
        // Update the power and turn again
        power = Controller.Axis3.position();
        turn = Controller.Axis1.position();

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