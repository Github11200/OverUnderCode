using namespace vex;

extern vex::brain Brain;

// VEXcode devices
extern vex::controller Controller;

// The drivetrain motors on the robot
extern vex::motor FrontRight;
extern vex::motor FrontLeft;
extern vex::motor BackRight;
extern vex::motor BackLeft;

extern vex::motor_group Right;
extern vex::motor_group Left;

// Motors for other subsystems
extern vex::motor Catapult;
extern vex::motor Intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);