#include "vex.h"

using namespace vex;

// 0.01 x
/// @brief Controls the drivetrain based on the joystick inputs
/// @return 0
int JoystickControl()
{
    double power = Controller.Axis3.position();
    double turn = Controller.Axis1.position();
    float deadZone = 5;

    while (true) {
        power = Controller.Axis3.position();
        turn = Controller.Axis1.position();

        if (power > deadZone || power < -deadZone)
            power > 0 ? power = Math.pow(power, 2) * 0.01 : power = -(Math.pow(power, 2) * 0.01);
        
        if (turn > deadZone || turn < -deadZone)
            turn > 0 ? turn = Math.pow(turn, 2) * 0.01 : turn = -(Math.pow(turn, 2) * 0.01);

        Left.spin(vex::forward, power - turn, vex::percentUnits::pct);

        vex::task::sleep(25);
    }

    return 0;
}