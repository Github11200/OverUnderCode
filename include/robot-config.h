using namespace vex;

extern brain Brain;

// VEXcode devices
extern vex::controller Controller;

extern vex::motor FrontRight;
extern vex::motor FrontLeft;
extern vex::motor MiddleRight;
extern vex::motor MiddleLeft;
extern vex::motor BackRight;
extern vex::motor BackLeft;

extern vex::motor_group Right;
extern vex::motor_group Left;

// Motors for other subsystems
extern vex::motor Catapult;
extern vex::motor Blocker;
extern vex::motor Intake;

// Pistons
extern digital_out wings;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);