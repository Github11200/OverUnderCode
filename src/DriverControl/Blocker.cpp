#include "../../include/DriverControl/Blocker.h"

using namespace vex;
using namespace std;

void deploy()
{
    Blocker.spinFor(vex::directionType::rev, 1, vex::timeUnits::sec, 100, vex::velocityUnits::pct);
    Blocker.stop(vex::brakeType::coast);
}

void rewindBlocker()
{
    while (Controller.ButtonDown.pressing())
        Blocker.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);

    Blocker.stop(vex::brakeType::hold);
}