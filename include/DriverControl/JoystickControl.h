#include "vex.h"

using namespace vex;

// 0.01 x
void JoystickControl()
{
    double power = Controller.Axis3.position();
    double turn = Controller.Axis1.position();
}