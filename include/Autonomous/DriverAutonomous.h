#ifndef DRIVER_AUTONOMOUS_H
#define DRIVER_AUTONOMOUS_H

#include "vex.h"
#include "../DriverControl/Catapult.h"
#include <vector>

using namespace vex;
using namespace std;

class DriverAutonomous
{
private:
    CatapultHandler *catapult;

public:
    DriverAutonomous(CatapultHandler *catapultHandler);

    /// @brief This function will start recording all of the button presses and joystick movements
    void record();

    /// @brief This method will execute all of the commands given to it
    void execute();
};

#endif