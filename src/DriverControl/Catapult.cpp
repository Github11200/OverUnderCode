#include "../../include/DriverControl/Catapult.h"

using namespace vex;

void CatapultHandler::rewind()
{
    // Bring the catapult back into the down position
    while (CatapultRotation.position(vex::rotationUnits::deg) < 81)
    {
        CatapultRight.spin(vex::directionType::rev, 35, vex::percentUnits::pct);
        CatapultLeft.spin(vex::directionType::fwd, 35, vex::percentUnits::pct);
    }

    Catapult.stop(vex::brakeType::hold);
}

void CatapultHandler::buttons()
{
    // THE L1 BUTTON IS FOR SINGLE CATAPULT FIRE
    if (Controller.ButtonLeft.pressing())
        this->singleFire();
    else if (Controller.ButtonDown.pressing()) // THE L2 BUTTON IS FOR RAPID FIRE
        this->rapidFire();

    this->rewind();
    this->isCatapultDown = true;
}

void CatapultHandler::singleFire()
{
    // If the catapult is down then spin the motor in reverse for 1 second to shoot it
    if (this->isCatapultDown)
    {
        CatapultRight.spin(vex::directionType::rev, 70, vex::percentUnits::pct);
        CatapultLeft.spin(vex::directionType::fwd, 70, vex::percentUnits::pct);
        wait(0.2, vex::timeUnits::sec);
        this->isCatapultDown = false;
    }
}

void CatapultHandler::rapidFire()
{
    // While the user is pressing the l2 button, continue spinning the catapult
    while (Controller.ButtonL2.pressing())
    {
        CatapultRight.spin(vex::directionType::rev, 70, vex::percentUnits::pct);
        CatapultLeft.spin(vex::directionType::fwd, 70, vex::percentUnits::pct);
    }
}