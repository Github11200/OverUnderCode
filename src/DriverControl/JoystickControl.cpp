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

    // It will use another way of calculating the joystick powers
    bool flipControls = false;

    double leftPower = 0;
    double rightPower = 0;
    double targetLeft = 0;
    double targetRight = 0;

    // Variables for PID, it is an array where error[0] = left side error and error[1] = right side error
    double error[2] = {0, 0};
    double previousError[2] = {0, 0};
    double derivative[2] = {0, 0};

    // PID constants
    double kP = 0.01;
    double kD = 0.01;

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
        y = -Controller.Axis1.position();
        x = Controller.Axis3.position();

        // Check if the values are within the deadzone, if so stop the motors and just continue
        if (x <= deadZone && x >= -deadZone || y <= deadZone && y >= -deadZone)
        {
            Left.stop(vex::brakeType::coast);
            Right.stop(vex::brakeType::coast);
            continue;
        }

        // Calculate the power and turn values by mapping them from 100% to 12 Volts
        power >
                0
            ? power = pow(power, 2) / (100 / 12)
            : power = -(pow(power, 2) / (100 / 12));

        // power *= 0.12 // THIS IS FOR LINEAR POWER

        turn >
                0
            ? turn = pow(turn, 2) / (100 / 12)
            : turn = -(pow(turn, 2) / (100 / 12));

        // turn *= 0.12 // THIS IS FOR LINEAR TURNING

        if (flipControls)
        {
            leftPower = power + turn;
            rightPower = power - turn;
        }
        else
        {
            leftPower = power - turn;
            rightPower = power + turn;
        }

        /******************
                PID
        ******************/

        error[0] = leftPower - Left.voltage(vex::voltageUnits::volt);
        error[1] = rightPower - Right.voltage(vex::voltageUnits::volt);

        derivative[0] = error[0];
        derivative[1] = error[1];

        leftPower = (error[0] * kP) + (derivative[0] * kD);
        rightPower = (error[1] * kP) + (derivative[1] * kD);

        // Spin the motors based on the power and turn
        Left.spin(vex::forward, leftPower, vex::voltageUnits::volt);
        Right.spin(vex::forward, rightPower, vex::voltageUnits::volt);

        previousError[0] = error[0];
        previousError[1] = error[1];

        vex::task::sleep(25);
    }
}