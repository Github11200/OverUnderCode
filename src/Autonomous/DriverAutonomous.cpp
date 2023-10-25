#include "../../include/Autonomous/DriverAutonomous.h"

using namespace vex;
using namespace std;

/*************************************************************************
    VALUES FOR THE COMMANDS STRING:
        1 -> Joystick forward/backward movement
        2 -> Joystick left/right movement
        3 -> Catapult single fire
        4 -> Catapult rapid fire
        5 -> Extend intake
        6 -> Rotate the intake to have it intake tri balls
        7 -> Rotate the intake to have it outtake tri balls
        8 -> Extend the right wing
        9 -> Extend the left wing
*************************************************************************/

DriverAutonomous::DriverAutonomous(CatapultHandler *catapultHandler)
{
    this->catapult = catapultHandler;
}

void DriverAutonomous::record()
{
    // Print out the joystick positions on the controller
    cout << Controller.Axis3.position() << ",";
    cout << Controller.Axis1.position() << ",";

    // Print out whether the L1 and/or L2 buttons (for catapult) are being pressed
    cout << Controller.ButtonL1.pressing() << ",";
    cout << Controller.ButtonL2.pressing() << ",";

    // Print out whether the Up, R1, and/or R2 buttons (for intake) are being pressed
    cout << Controller.ButtonUp.pressing() << ",";
    cout << Controller.ButtonR1.pressing() << ",";
    cout << Controller.ButtonR2.pressing() << ",";

    // Check if the X button (for wings) if being pressed
    cout << Controller.ButtonX.pressing() << ",";
}

void DriverAutonomous::execute()
{
    vector<int> commands = {4, 5, 6, 6};
    int commandNumber = 1;

    bool isCatapultRapidFireOn = false;
    bool wingsExtended = false;
    double power = 0;
    double turn = 0;

    for (int i = 0; i < commands.size(); ++i)
    {
        switch (commandNumber)
        {
        // This checks if we are at the second command, so now we know both the power and turn
        // of the joysticks, and we can calculate them and turn the motors
        case 2:
            power = commands[i - 1];
            turn = commands[i];

            // Calculate the turn and power of the motors
            power > 0 ? power = pow(power, 2) * 0.01 : power = -(pow(power, 2) * 0.01);
            turn > 0 ? turn = pow(turn, 2) * 0.01 : turn = -(pow(turn, 2) * 0.01);

            // Spin the motors based on the inputs
            Left.spin(vex::forward, power - turn, vex::percentUnits::pct);
            Right.spin(vex::forward, power + turn, vex::percentUnits::pct);

            break;

        // This is if we had pressed L1, so this will fire the catapult once
        case 3:
            if (commands[i])
            {
                this->catapult->singleFire();
                this->catapult->rewind();
            }
            break;

        // This is if we had pressed L2, so it will rapid fire the catapult or it will
        // stop it depending on whether or not it is already rapid firing
        case 4:
            if (commands[i])
            {
                if (isCatapultRapidFireOn)
                {
                    this->catapult->rewind();
                    isCatapultRapidFireOn = false;
                }
                else
                    this->catapult->rapidFire();
            }
            break;

        // This checks if we had pressed the up button, so it will extend the intake
        case 5:
            if (commands[i])
            {
                IntakePiston.set(true);
                wait(1, vex::timeUnits::sec);
                IntakePiston.set(false);
            }
            break;

        // This checks if we pressed R1, and it will make the intake intake otherwise it will just have
        // it stopped at coast
        case 6:
            commands[i] ? Intake.spin(vex::directionType::fwd, 100, vex::percentUnits::pct) : Intake.stop(vex::brakeType::coast);
            break;

        // This checks if we pressed R2, and it will make the intake outtake otherwise it will just have
        // it stopped at coast
        case 7:
            commands[i] ? Intake.spin(vex::directionType::rev, 100, vex::percentUnits::pct) : Intake.stop(vex::brakeType::coast);
            break;

        // If the X button was pressed then either extend or retract the wings based on their current state
        case 8:
            if (commands[i])
                wings.set(!wingsExtended);
            break;

        default:
            break;
        }

        // If the command number is 8 then bring it back to one otherwise just increment it
        commandNumber == 8 ? commandNumber = 1 : ++commandNumber;
    }
}