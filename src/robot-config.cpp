#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller = controller(primary);

// The drivetrain motors on the robot
motor FrontRight = motor(PORT6, ratio6_1, false);
motor FrontLeft = motor(PORT7, ratio6_1, false);
motor BackRight = motor(PORT8, ratio6_1, false);
motor BackLeft = motor(PORT9, ratio6_1, false);

motor_group Right = motor_group(FrontRight, BackRight);
motor_group Left = motor_group(FrontLeft, BackLeft);

// Motors for other subsystems
motor Catapult = motor(PORT10, ratio36_1, false);
motor Intake = motor(PORT11, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
    // nothing to initialize
}