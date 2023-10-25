#include "../../include/DriverControl/Catapult.h"

using namespace vex;

void CatapultHandler::rewind()
{
    // Bring the catapult back into the down position
    while (CatapultRotationSensor.position(vex::rotationUnits::deg) < 94.5)
        Catapult.spin(vex::directionType::fwd, 100, vex::percentUnits::pct);

    Catapult.stop(vex::brakeType::hold);
}

void CatapultHandler::buttons()
{
    // THE L1 BUTTON IS FOR SINGLE CATAPULT FIRE
    if (Controller.ButtonL1.pressing())
        this->singleFire();
    else if (Controller.ButtonL2.pressing()) // THE L2 BUTTON IS FOR RAPID FIRE
        this->rapidFire();

    this->rewind();
    this->isCatapultDown = true;
}

void CatapultHandler::singleFire()
{
    // If the catapult is down then spin the motor in reverse for 1 second to shoot it
    if (this->isCatapultDown)
    {
        Catapult.spinFor(vex::directionType::fwd, 1, vex::timeUnits::sec);
        this->isCatapultDown = false;
    }
}

void CatapultHandler::rapidFire()
{
    // While the user is pressing the l2 button, continue spinning the catapult
    while (Controller.ButtonL2.pressing())
        Catapult.spin(vex::directionType::fwd, 100, vex::percentUnits::pct);
}