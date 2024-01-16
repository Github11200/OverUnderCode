#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller;

motor FrontRight = motor(PORT20, ratio6_1, false);  // Done
motor FrontLeft = motor(PORT10, ratio6_1, true);    // Done
motor MiddleRight = motor(PORT17, ratio6_1, false); // Done
motor MiddleLeft = motor(PORT9, ratio6_1, true);    // Done
motor BackRight = motor(PORT18, ratio6_1, false);   // Done
motor BackLeft = motor(PORT8, ratio6_1, true);      // Done

// Motors for other subystems
motor Catapult = motor(PORT1, ratio36_1, false); // Done
motor Intake = motor(PORT21, ratio36_1, false);  // Done
motor Blocker = motor(PORT15, ratio18_1, false); // Done

// Drivetrain motor groups
motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);

// Pistons
digital_out wings = digital_out(Brain.ThreeWirePort.H);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
    // nothing to initialize
}