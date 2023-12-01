#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller = controller(primary);

// The drivetrain motors on the robot
motor FrontRight = motor(PORT16, ratio6_1, false); // Done
motor FrontLeft = motor(PORT1, ratio6_1, false);   // Done
motor BackRight = motor(PORT6, ratio6_1, false);   // Done
motor BackLeft = motor(PORT13, ratio6_1, false);   // Done

// Motors for other subsystems
motor CatapultRight = motor(PORT14, ratio36_1, false); // Done
motor CatapultLeft = motor(PORT15, ratio36_1, false);  // Done
motor Intake = motor(PORT12, ratio36_1, false);        // Done

// Motor groups
motor_group Right = motor_group(FrontRight, BackRight);
motor_group Left = motor_group(FrontLeft, BackLeft);
motor_group Catapult = motor_group(CatapultRight, CatapultLeft);

// Sensors
limit CatapultLimitSwitch = limit(Brain.ThreeWirePort.H); // Done
inertial Inertial = inertial(PORT3);
encoder RightEncoder = encoder(Brain.ThreeWirePort.C); // Done
encoder BackEncoder = encoder(Brain.ThreeWirePort.E);  // Done

// Pistons
digital_out RightWing = digital_out(Brain.ThreeWirePort.A);
digital_out LeftWing = digital_out(Brain.ThreeWirePort.B);

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