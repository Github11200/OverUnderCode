#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller = controller(primary);

// The drivetrain motors on the robot
motor FrontRight = motor(PORT13, ratio6_1, false);
motor FrontLeft = motor(PORT16, ratio6_1, false);
motor BackRight = motor(PORT15, ratio6_1, false);
motor BackLeft = motor(PORT14, ratio6_1, false);

// Motors for other subsystems
motor Catapult = motor(PORT12, ratio36_1, false);
motor Intake = motor(PORT17, ratio36_1, false);
motor ClimbMotorRight = motor(PORT10, ratio36_1, false);
motor ClimbMotorLeft = motor(PORT21, ratio36_1, false);

// Motor groups
motor_group Right = motor_group(FrontRight, BackRight);
motor_group Left = motor_group(FrontLeft, BackLeft);
motor_group ClimbMotors = motor_group(ClimbMotorRight, ClimbMotorLeft);

// Sensors
rotation CatapultRotationSensor = rotation(PORT11, false);
inertial Inertial = inertial(PORT3);

// Pistons
digital_out wings = digital_out(Brain.ThreeWirePort.A);
digital_out IntakePiston = digital_out(Brain.ThreeWirePort.B);

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