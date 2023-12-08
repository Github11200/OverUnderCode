#include "../../include/DriverControl/JoystickControl.h"

using namespace vex;
using namespace std;

int sgn(double num)
{
    if (num >= 0)
        return 1;
    else
        return -1;
}

double findMinAngle(double targetAngle, double currentHeading)
{
    double minAngle = targetAngle - currentHeading;

    if (minAngle > 180 || minAngle < -180)
        minAngle = -1 * sgn(minAngle) * (360 - fabs(minAngle));

    return minAngle;
}

int JoystickControl()
{
    // Get the power and turn from the controller joysticks, and set the deadzone to 5 (this reduces controller drift)
    double power = 0;
    double turn = 0;
    float deadZone = 5;

    double x = 0;
    double y = 0;
    double angle = 0;

    // If the drive mode is false, then it'll drive like normal, and if it is true then
    // it will use another way of calculating the joystick powers
    bool driveMode = false;

    bool flipControls = false;

    double left = 0;
    double right = 0;

    // Run this as a task until the entire program stops
    while (true)
    {
        // If the x button is pressed then switch the drive mode
        if (Controller.ButtonA.pressing())
        {
            driveMode = !driveMode;

            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(0, 0);
            Controller.Screen.print(driveMode ? "TRUE" : "FALSE");
            Brain.Screen.clearScreen();
            Brain.Screen.setFillColor(driveMode ? vex::color::green : vex::color::red);
            Brain.Screen.drawRectangle(0, 0, 48, 12);

            wait(15, vex::timeUnits::msec);
        }

        // Check what drive mode it is
        if (driveMode)
        {
            // Update the x and y values so we can figure out the location of the joystick
            x = Controller.Axis3.position();
            y = -Controller.Axis1.position();

            // Check if the values are within the deadzone, if so stop the motors and just continue
            if (x <= deadZone && x >= -deadZone && y <= deadZone && y >= -deadZone)
            {
                Left.stop(vex::brakeType::coast);
                Right.stop(vex::brakeType::coast);
            }

            // Calculate the power by getting the length of the hypotenuse
            power = sqrt(pow(x, 2) + pow(y, 2));

            // Get the angle of the joystick
            angle = atan2(y, x) * (180 / M_PI) < 0 ? (atan2(y, x) * (180 / M_PI)) + 360 : atan2(y, x) * (180 / M_PI);

            // Find the minimum about the robot has to turn in order to get to the angle of the joystick and make that the turn power
            turn = findMinAngle(angle, Inertial.heading(vex::rotationUnits::deg));
        }
        else
        {
            // Update the x and y values so we can figure out the location of the joystick
            power = -Controller.Axis1.position();
            turn = Controller.Axis3.position();

            // Check if the values are within the deadzone, if so stop the motors and just continue
            if (x <= deadZone && x >= -deadZone && y <= deadZone && y >= -deadZone)
            {
                Left.stop(vex::brakeType::coast);
                Right.stop(vex::brakeType::coast);
            }
        }

        // Calculate the power and turn
        power >
                0
            ? power = pow(power, 2) * 0.01
            : power = -(pow(power, 2) * 0.01);

        turn > 0 ? turn = pow(turn, 2) * 0.01 : turn = -(pow(turn, 2) * 0.01);

        if (flipControls)
        {
            left = power + turn;
            right = power - turn;
        }
        else
        {
            left = power - turn;
            right = power + turn;
        }

        // Spin the motors based on the power and turn
        Left.spin(vex::forward, left, vex::percentUnits::pct);
        Right.spin(vex::forward, right, vex::percentUnits::pct);

        vex::task::sleep(25);
    }
}