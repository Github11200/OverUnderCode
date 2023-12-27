#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller = controller(primary);

// The drivetrain motors on the robot
motor FrontRight = motor(PORT14, ratio6_1, false);
motor FrontLeft = motor(PORT13, ratio6_1, false);
motor MiddleRight = motor(PORT15, ratio6_1, false);
motor MiddleLeft = motor(PORT18, ratio6_1, false);
motor BackRight = motor(PORT11, ratio6_1, false);
motor BackLeft = motor(PORT16, ratio6_1, false);

// Motors for other subsystems
motor Catapult = motor(PORT18, ratio36_1, false);
motor Intake = motor(PORT12, ratio36_1, false);

// Motor groups
motor_group Right = motor_group(FrontRight, MiddleRight, BackRight);
motor_group Left = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor_group Catapult = motor_group(CatapultRight, CatapultLeft);

// Sensors
rotation CatapultRotation = rotation(PORT20);
inertial Inertial = inertial(PORT19);
encoder RightEncoder = encoder(Brain.ThreeWirePort.C);
encoder BackEncoder = encoder(Brain.ThreeWirePort.E);

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