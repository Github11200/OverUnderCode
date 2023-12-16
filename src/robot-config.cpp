#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller = controller(primary);

// The drivetrain motors on the robot
motor FrontRight = motor(PORT14, ratio6_1, false); // DONE
motor FrontLeft = motor(PORT13, ratio6_1, false);  // DONE
motor BackRight = motor(PORT11, ratio6_1, false);  // DONE
motor BackLeft = motor(PORT16, ratio6_1, false);   // DONE

// Motors for other subsystems
motor CatapultRight = motor(PORT17, ratio36_1, false); // DONE
motor CatapultLeft = motor(PORT18, ratio36_1, false);  // DONE
motor Intake = motor(PORT12, ratio36_1, false);        // DONE

// Motor groups
motor_group Right = motor_group(FrontRight, BackRight);
motor_group Left = motor_group(FrontLeft, BackLeft);
motor_group Catapult = motor_group(CatapultRight, CatapultLeft);

// Sensors
rotation CatapultRotation = rotation(PORT20);
inertial Inertial = inertial(PORT19);                  // DONE
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