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

double remap(double xAxis)
{
    double result = 0;
    double cConstants[4] = {
        0, 0.736, -0.43, 1};

    result += pow((1 - xAxis), 3) * cConstants[0];
    result += 3 * xAxis * pow((1 - xAxis), 2) * cConstants[1];
    result += 3 * pow(xAxis, 2) * (1 - xAxis) * cConstants[2];
    result += pow(xAxis, 3) * cConstants[3];

    return result * 100;
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
            flipControls = !flipControls;

            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(0, 0);
            Controller.Screen.print(flipControls ? "TRUE" : "FALSE");
            Brain.Screen.clearScreen();
            Brain.Screen.setFillColor(flipControls ? vex::color::green : vex::color::red);
            Brain.Screen.drawRectangle(0, 0, 48, 12);

            wait(100, vex::timeUnits::msec);
        }

        // Update the x and y values so we can figure out the location of the joystick
        power = Controller.Axis3.position();
        turn = -Controller.Axis1.position();

        // Check if the values are within the deadzone, if so stop the motors and just continue
        if (x <= deadZone && x >= -deadZone && y <= deadZone && y >= -deadZone)
        {
            Left.stop(vex::brakeType::coast);
            Right.stop(vex::brakeType::coast);
        }

        // Calculate the power using the curve (we will leave the turning linear)
        power >
                0
            ? power = ((sin((M_PI * (power / 100)) - 1.57) * 0.5) + 0.5) * 100
            : power = (-((sin((M_PI * (power / 100)) - 1.57) * 0.5) + 0.5)) * 100;
        // power > 0 ? power = remap(power / 100) : power = (remap(power / 100));

        turn >
                0
            ? turn = ((sin((M_PI * (turn / 100)) - 1.57) * 0.5) + 0.5) * 100
            : turn = (-((sin((M_PI * (turn / 100)) - 1.57) * 0.5) + 0.5)) * 100;

        // turn > 0 ? turn = remap(turn / 100) : turn = (remap(turn / 100));

        if (flipControls)
        {
            power = power;
            turn = turn;
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
