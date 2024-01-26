#include "vex.h"

void default_constants()
{
    chassis.set_drive_constants(12, 1.9, 0.008, 10, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(12, .4, .03, 3, 15);
    chassis.set_swing_constants(12, 1, .001, 2, 15);
    chassis.set_drive_exit_conditions(1.5, 300, 5000);
    chassis.set_turn_exit_conditions(1, 300, 3000);
    chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants()
{
    default_constants();
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
}

void drive_test()
{
    chassis.drive_distance(6);
    chassis.drive_distance(12);
    chassis.drive_distance(18);
    chassis.drive_distance(-36);
}

void turn_test()
{
    chassis.turn_to_angle(5);
    chassis.turn_to_angle(30);
    chassis.turn_to_angle(90);
    chassis.turn_to_angle(225);
    chassis.turn_to_angle(0);
}

void swing_test()
{
    chassis.left_swing_to_angle(90);
    chassis.right_swing_to_angle(0);
}

void full_test()
{
    chassis.drive_distance(24);
    chassis.turn_to_angle(-45);
    chassis.drive_distance(-36);
    chassis.right_swing_to_angle(-90);
    chassis.drive_distance(24);
    chassis.turn_to_angle(0);
}

void odom_test()
{
    chassis.set_coordinates(0, 0, 0);
    while (1)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(0, 50, "X: %f", chassis.get_X_position());
        Brain.Screen.printAt(0, 70, "Y: %f", chassis.get_Y_position());
        Brain.Screen.printAt(0, 90, "Heading: %f", chassis.get_absolute_heading());
        Brain.Screen.printAt(0, 110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
        Brain.Screen.printAt(0, 130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
        task::sleep(20);
    }
}

void tank_odom_test()
{
    odom_constants();
    chassis.set_coordinates(0, 0, 0);
    chassis.turn_to_point(24, 24);
    chassis.drive_to_point(24, 24);
    chassis.drive_to_point(0, 0);
    chassis.turn_to_angle(0);
}

void holonomic_odom_test()
{
    odom_constants();
    chassis.set_coordinates(0, 0, 0);
    chassis.holonomic_drive_to_point(0, 18, 90);
    chassis.holonomic_drive_to_point(18, 0, 180);
    chassis.holonomic_drive_to_point(0, 18, 270);
    chassis.holonomic_drive_to_point(0, 0, 0);
}

void far_side_autonomous()
{
    // Intake the tri ball in front of the robot
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::rev, 1.55, vex::rotationUnits::rev, false);
    chassis.drive_distance(6, 0, 10, 6, .5, 100, 200);
    wait(0.8, vex::timeUnits::sec);

    // Move the robot back and line it up to take the tri ball out of the corner
    chassis.drive_distance(-32.5, 0, 10, 6, .5, 100, 800);
    chassis.turn_to_angle(-45, 10, .5, 100, 500);

    // Take the tri ball out of the corner
    chassis.drive_distance(-23, 315, 10, 6, .5, 100, 600);
    chassis.turn_to_angle(-45, 10, .5, 100, 400);

    // Push the tri balls in and move forward again
    chassis.drive_distance(-15, 270, 12, 12, .5, 100, 600);
    chassis.drive_distance(10, 270, 10, 6, .5, 100, 600);

    // // Turn around and outtake the tri ball that was already inside the intake
    chassis.turn_to_angle(90, 10, .5, 100, 800);
    Intake.setVelocity(100, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 1.4, vex::rotationUnits::rev, false);
    chassis.drive_distance(13, 91, 12, 6, .5, 100, 600);
    chassis.drive_distance(-15, 91, 10, 6, .5, 100, 600);

    // Turn to face the tri ball on the left, move forward, and intake it
    chassis.turn_to_angle(25, 10, .5, 100, 800);
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::rev, 6, vex::rotationUnits::rev, false);
    chassis.drive_distance(49, 25, 12, 12, 0.5, 200, 1200);

    // // Move the robot back, turn to face towards the goal, move forward, then outtake the tri ball
    chassis.drive_distance(-2, 90, 10, 6, .5, 100, 800);
    chassis.turn_to_angle(100, 10, .5, 100, 500);
    chassis.drive_distance(19, 100, 10, 6, .5, 100, 800);
    chassis.left_swing_to_angle(180, 12, 2, 200, 500, 1, 0.001, 2, 15);
    Intake.setVelocity(90, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 2, vex::rotationUnits::rev, false);
    chassis.drive_distance(20, 180, 10, 6, .5, 100, 800);
    // Intake.setVelocity(90, vex::percentUnits::pct);
    // Intake.spinFor(vex::directionType::fwd, 1, vex::rotationUnits::rev, false);
    // chassis.drive_distance(18, 143,10,6,.5,100,800);
    // chassis.drive_distance(-3,143,10,6,.5,100,800);
    // chassis.turn_to_angle(13,10,.5,100,800);;

    // // // // Turn, move forward and intake another tri ball
    // Intake.setVelocity(90, vex::percentUnits::pct);
    // Intake.spinFor(vex::directionType::rev, 6, vex::rotationUnits::rev, false);
    // chassis.drive_distance(8,13,10,6,.5,100,800);

    // // // // Get the second tri ball and outtake
    // chassis.turn_to_angle(180,10,.5,100,800);
    // Intake.spinFor(vex::directionType::fwd, 2, vex::rotationUnits::rev, false);
    // chassis.drive_distance(13,180,11,6,.5,100,800);

    // Move back, turn to face the third tri ball, and go forward to intake it
    chassis.drive_distance(-17, 180, 10, 6, .5, 100, 800);
    chassis.turn_to_angle(11, 10, .5, 100, 800);
    Intake.spinFor(vex::directionType::rev, 3, vex::rotationUnits::rev, false);
    chassis.drive_distance(18, 10, 10, 6, .5, 100, 800);

    // Turn to face the goal again, and outtake the tri ball
    chassis.turn_to_angle(180, 10, .5, 100, 800);
    Intake.setVelocity(100, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 3, vex::rotationUnits::rev, false);
    wait(0.05, vex::timeUnits::sec);
    chassis.drive_distance(29, 180, 12, 6, .5, 100, 800);
    chassis.drive_distance(-10, 180, 12, 6, .5, 100, 800);

    // // // Move back, turn, move back again, and turn a bit more to touch the pipe
    // chassis.drive_distance(-30, 180,10,6,.5,100,800);
    // chassis.turn_to_angle(90);
    // wings.set(true);
    // chassis.drive_distance(-40,90,10,6,.5,100,800);
    // chassis.turn_to_angle(195);
}

void close_side_autonomous()
{
    // Turn the robot towards the goal, and move it forward
    chassis.turn_to_angle(45, 10);
    chassis.drive_distance(26, 45);

    // Turn to face the goal, outtake the tri ball, and push it in
    chassis.turn_to_angle(90);
    Intake.setVelocity(95, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 2, vex::rotationUnits::rev, false);
    wait(0.2, vex::timeUnits::sec);
    chassis.drive_distance(10, 90, 12, 12, 1.5, 200, 300);

    // Move back again, and align the robot to get ready to take the tri ball out of the corner
    chassis.drive_distance(-12);
    chassis.turn_to_angle(45);

    // // Move back and turn to take the tri ball out of the corner
    wings.set(true);
    chassis.drive_distance(-26, 45);
    wings.set(false);
    chassis.turn_to_angle(0);
    chassis.drive_distance(-32, 0);
    wings.set(true);
    // // Turn back to 0 degrees, and move back to touch the pole
    // chassis.turn_to_angle(-27);
    // chassis.drive_distance(-37, 0);
}