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

void skills_constants()
{
    chassis.set_drive_constants(12, 2, 0.008, 10, 0);
    chassis.set_swing_constants(12, 1.3, 0.001, 2, 15);
    chassis.set_drive_exit_conditions(1.5, 200, 5000);
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
    blocker.set(true);
    wait(0.1, vex::timeUnits::sec);
    blocker.set(false);

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
    blocker.set(true);
    wait(0.1, vex::timeUnits::sec);
    blocker.set(false);

    // Turn the robot towards the goal, and move it forward
    chassis.turn_to_angle(33, 10);
    wings.set(true);
    wait(0.2, vex::timeUnits::sec);
    chassis.drive_distance(24, 33);
    chassis.turn_to_angle(50);
    chassis.drive_distance(5.2, 50);
    wings.set(false);

    // Turn to face the goal, outtake the tri ball, and push it in
    chassis.turn_to_angle(90);
    Intake.setVelocity(95, vex::percentUnits::pct);
    Intake.spinFor(vex::directionType::fwd, 2, vex::rotationUnits::rev, false);
    wait(0.2, vex::timeUnits::sec);
    chassis.drive_distance(10, 90, 12, 12, 1.5, 200, 300);

    // Move back again, and align the robot to get ready to take the tri ball out of the corner
    chassis.drive_distance(-15);
    chassis.turn_to_angle(45);

    // Move back and turn to take the tri ball out of the corner
    chassis.drive_distance(-23, 45);
    chassis.turn_to_angle(0);
    chassis.drive_distance(-33, 0);
    wings.set(true);
    // // Turn back to 0 degrees, and move back to touch the pole
    // chassis.turn_to_angle(-27);
    // chassis.drive_distance(-37, 0);
}

void skills_autonomous()
{
    blocker.set(true);
    wait(0.1, vex::timeUnits::sec);
    blocker.set(false);

    // Turn right, move back, and swing to push the tri ball into the goal
    chassis.turn_to_angle(45);
    chassis.drive_distance(-26);
    chassis.turn_to_angle(90);
    chassis.drive_distance(-9, 90, 12, 12);
    chassis.drive_distance(9);

    // Move forwad, turn, move forward again, turn again, move back, and deploy wings
    // to touch the match loading pipe for match loading
    chassis.drive_distance(9, 90);
    chassis.turn_to_angle(25);
    chassis.drive_distance(11, 25);
    chassis.turn_to_angle(341);
    chassis.drive_distance(-5, 341);
    wings.set(true);

    // Start the slapper, and put the wings up again
    Catapult.spin(vex::directionType::fwd, 90, vex::percentUnits::pct);
    wait(1, vex::timeUnits::sec);
    Catapult.stop(vex::brakeType::coast);
    wings.set(false);

    // Turn, move forward, and turn again to align with the goal
    chassis.turn_to_angle(36);
    chassis.drive_distance(20, 36);
    chassis.turn_to_angle(0);
    chassis.turn_to_angle(180);

    // Go through the alley way
    chassis.drive_distance(-74, 180);

    // Swing, drive forward, swing again, and push the tri balls into the goal
    chassis.left_swing_to_angle(135);
    chassis.drive_distance(-17, 135);
    chassis.left_swing_to_angle(90);
    chassis.drive_distance(-15, 90, 12, 12, 0.5, 200, 300);
    chassis.drive_distance(15, 90, 12, 12, 0.5, 200, 300);
    chassis.drive_distance(-15, 90, 12, 12, 0.5, 200, 300);
    chassis.drive_distance(12, 90, 12, 12, 0.5, 200, 300);

    // Swing to face the other way, move backwards, and turn again, and push the tri balls in
    chassis.turn_to_angle(15);
    chassis.drive_distance(-44, 15);
    chassis.turn_to_angle(90);
    wings.set(true);
    chassis.drive_distance(-15, 100);
    chassis.turn_to_angle(170);
    chassis.drive_distance(-24, 170);

    // Move it forward, turn, move it back, and turn so it's facing the goal again
    chassis.drive_distance(33, 170);
    chassis.turn_to_angle(90);
    chassis.drive_distance(-20, 90);
    chassis.turn_to_angle(180);

    // Push the tri balls in from the middle
    chassis.drive_distance(-28, 180);
    chassis.drive_distance(7, 180);
    chassis.drive_distance(-7, 180);
    chassis.drive_distance(7, 180);
    wings.set(false);

    // Move forward, turn, move back, and turn again to face the goal
    chassis.drive_distance(28, 180);
    chassis.turn_to_angle(90);
    chassis.drive_distance(-25, 90);
    chassis.turn_to_angle(220);

    // Push the tri balls in for the last time
    chassis.drive_distance(-28, 220);
    chassis.drive_distance(8, 220);
    chassis.drive_distance(-8, 220);
    chassis.drive_distance(8, 220);
    chassis.turn_to_angle(180);
    chassis.drive_distance(10, 180);

    // Move back, turn to face the goal, and push the tri balls in again chassis.drive_distance(-23, 180);
    chassis.drive_distance(10, 180);
    chassis.turn_to_angle(180);
    wings.set(true);
    chassis.drive_distance(-26, 180);
    chassis.drive_distance(5, 180);
    chassis.drive_distance(-5, 180);
    chassis.drive_distance(5, 180);
    wings.set(false);

    // // Move forward again, turn, move back again, and turn to face the goal again
    // chassis.drive_distance(20, 180);
    // chassis.turn_to_angle(90);
    // chassis.drive_distance(-6, 90);
    // chassis.turn_to_angle(190);

    // Move back to push in the tri balls
    // wings.set(true);
    // chassis.drive_distance(-19, 180);
    // chassis.drive_distance(-26, 180);
    // chassis.drive_distance(5, 180);
    // chassis.drive_distance(-5, 180);
    // chassis.drive_distance(5, 180);
}

void driver_skills_beginning()
{
    blocker.set(true);
    wait(0.1, vex::timeUnits::sec);
    blocker.set(false);

    // Turn right, move back, and swing to push the tri ball into the goal
    chassis.turn_to_angle(45);
    chassis.drive_distance(-26);
    chassis.turn_to_angle(90);
    chassis.drive_distance(-9, 90, 12, 12);
    chassis.drive_distance(9);

    // Move forwad, turn, move forward again, turn again, move back, and deploy wings
    // to touch the match loading pipe for match loading
    chassis.drive_distance(9, 90);
    chassis.turn_to_angle(25);
    chassis.drive_distance(11, 25);
    chassis.turn_to_angle(341);
    chassis.drive_distance(-5, 341);
    wings.set(true);
}