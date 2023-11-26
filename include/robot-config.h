using namespace vex;

extern vex::brain Brain;

// VEXcode devices
extern vex::controller Controller;

// The drivetrain motors on the robot
extern vex::motor FrontRight;
extern vex::motor FrontLeft;
extern vex::motor BackRight;
extern vex::motor BackLeft;

// Motors for other subsystems
extern vex::motor Catapult;
extern vex::motor Intake;
extern vex::motor ClimbMotorRight;
extern vex::motor ClimbMotorLeft;

// Motor groups
extern vex::motor_group Right;
extern vex::motor_group Left;

// Sensors
extern limit CatapultLimitSwitch;
extern inertial Inertial;
extern encoder RightEncoder;
extern encoder BackEncoder;

// Pistons
extern digital_out RightWing;
extern digital_out LeftWing;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);