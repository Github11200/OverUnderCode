#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller = controller(primary);

// The drivetrain motors on the robot
motor FrontRight = motor(PORT20, ratio6_1, false);  // Done
motor FrontLeft = motor(PORT10, ratio6_1, false);   // Done
motor MiddleRight = motor(PORT17, ratio6_1, false); // Done
motor MiddleLeft = motor(PORT9, ratio6_1, false);   // Done
motor BackRight = motor(PORT18, ratio6_1, false);   // Done
motor BackLeft = motor(PORT8, ratio6_1, false);     // Done

// Motors for other subsystems
motor Catapult = motor(PORT1, ratio36_1, false); // Done
motor Intake = motor(PORT21, ratio36_1, false);  // Done
motor Blocker = motor(PORT15, ratio18_1, false); // Done

// Motor groups
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);
motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);

// Sensors
inertial Inertial = inertial(PORT14); // Done
// encoder RightEncoder = encoder(Brain.ThreeWirePort.C);
// encoder BackEncoder = encoder(Brain.ThreeWirePort.E);

// Pistons
digital_out wings = digital_out(Brain.ThreeWirePort.H);
// digital_out RightWing = digital_out(Brain.ThreeWirePort.A);
// digital_out LeftWing = digital_out(Brain.ThreeWirePort.B);

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