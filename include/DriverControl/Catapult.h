#ifndef CATAPULT_H
#define CATAPULT_H

#include "vex.h"

/// @brief This class handles all of the catapult functions
class CatapultHandler
{
private:
    bool isCatapultDown = true;

public:
    /// @brief This method will bring the catapult back down and get it ready to fire
    void rewind();

    /// @brief This method handles the button presses, and will shoot and rewind the cata depending on what buttons are pressed
    void buttons();

    /// @brief This will fire the catapult once
    void singleFire();

    /// @brief This will continuously fire the catapult until the driver lets go of the L2 button
    void rapidFire();

    /// @brief This will get the catapult un stuck by setting the motor to coast
    void getCatapultUnstuck();
};

#endif