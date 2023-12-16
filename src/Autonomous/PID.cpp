#include "../../include/Autonomous/PID.h"

using namespace vex;
using namespace std;

int PID::sgn(double num)
{
    if (num >= 0)
        return 1;
    else
        return -1;
}

double PID::findMinAngle(double targetAngle, double currentHeading)
{
    double minAngle = targetAngle - currentHeading;

    if (minAngle > 180 || minAngle < -180)
        minAngle = -1 * this->sgn(minAngle) * (360 - fabs(minAngle));

    return minAngle;
}

float PID::Inches_To_Degrees(float inches)
{
    float Wheel_Circumfrance = 2 * M_PI * 2;

    float degrees = (inches / Wheel_Circumfrance) * 360;

    return degrees;
}

bool PID::isInRange(double num, double target, double range)
{
    if (num >= target - range && num <= target + range)
        return true;
    else
        return false;
}

void PID::MoveToPoint(double targetX, double targetY, double targetTheta, bool isRelativeToZero, double desiredValue, double turnkPValue, double errorLoopEndValue, double turnErrorLoopEndValue, double kpValue)
{
    // The total power for turning and moving forward
    double power = 0;
    double turnPower = 0;

    // The errors both while moving forward and turning
    double error = 10;
    double previousError = 0;
    double turnError = 0;
    double previousTurnError = 0;

    double integral = 0;
    double turnIntegral = 0;

    double derivative = 0;
    double turnDerivative = 0;

    double angle = 0;

    // Constants
    float kP = kpValue;
    float kI = 0.01;
    float kD = 0.01;
    float wheelDiameter = 4;

    float turnkP = turnkPValue;
    float turnkI = 0.08;
    float turnkD = 0.05;
    int maxErrorForIntegral = 100;
    int maxTurnErrorForTurnIntegral = 90;
    int dT = 15;

    double leftPositionAverage = 0;
    double rightPositionAverage = 0;
    double averagePosition = 0;
    double inchesTraveled = 0;

    // If the robot's starting position is going to be from 0 every time (if we don't have time
    // to implement odometry) then set the position to 0 always
    if (isRelativeToZero)
    {
        Left.setPosition(0, vex::rotationUnits::deg);
        Right.setPosition(0, vex::rotationUnits::deg);
    }

    while (fabs(error) >= errorLoopEndValue || fabs(turnError) >= turnErrorLoopEndValue)
    {
        // cout << "Error: " << error << endl;
        // cout << "Turn Error: " << turnError << endl;
        // cout << "Turn Power: " << turnPower << endl;
        // cout << "Power: " << power << endl;
        // cout << "Inertial Heading: " << Inertial.heading(vex::rotationUnits::deg) << endl;

        // If the robot is starting relative to 0 then the average position will the the average
        // between the motors on the left side and the motors on the right side
        if (isRelativeToZero)
        {
            leftPositionAverage = -((FrontLeft.position(vex::rotationUnits::deg) + BackLeft.position(vex::rotationUnits::deg)) / 2);
            rightPositionAverage = ((FrontRight.position(vex::rotationUnits::deg) + BackRight.position(vex::rotationUnits::deg)) / 2);
            averagePosition = (leftPositionAverage + rightPositionAverage) / 2;
            inchesTraveled = ((averagePosition / 840) * wheelDiameter * M_PI);
        }

        /*=================================================================
                            Moving towards target point
        =================================================================*/

        /*****************************ERROR*****************************/
        error = (desiredValue - inchesTraveled);

        /*=================================================================
                            Turning towards target point
        =================================================================*/

        /*****************************TURN ERROR*****************************/
        angle = atan2(targetY - y, targetX - x) * (180 / M_PI);
        // if (angle < 0)
        //     angle += 360;
        turnError = this->findMinAngle(targetTheta, Inertial.heading(vex::rotationUnits::deg));

        // /*****************************TURN DERIVATIVE*****************************/
        turnDerivative = turnError - previousTurnError;

        // Calculate the powers for going straight and turning
        power = (error * kP);
        turnPower = ((turnError * turnkP) + (turnDerivative * turnkD));

        // Spin the motors based on the values
        Left.spin(vex::directionType::rev, power + turnPower, vex::voltageUnits::volt);
        Right.spin(vex::directionType::fwd, power - turnPower, vex::voltageUnits::volt);

        // Update the previous errors
        previousError = error;
        previousTurnError = turnError;

        wait(dT, vex::timeUnits::msec);
    }
}

void PID::Turn(double targetTheta, double turnkPValue, double errorValue)
{
    double turnPower = 0;

    // PID components
    double turnError = 10;
    double previousTurnError = 0;

    double turnIntegral = 0;

    double turnDerivative = 0;

    // Constants
    float turnkP = turnkPValue;
    float turnkI = 0.01;
    float turnkD = 0.02;
    int maxTurnErrorForTurnIntegral = 60;
    int dT = 15;

    while (fabs(turnError) >= errorValue)
    {
        // if (this->isInRange(fabs(turnError), fabs(previousTurnError), range))
        //     break;

        /*****************************TURN ERROR*****************************/
        turnError = this->findMinAngle(targetTheta, Inertial.heading(vex::rotationUnits::deg));

        /*****************************TURN INTEGRAL*****************************/
        fabs(turnError) < 0 || fabs(turnError) >= maxTurnErrorForTurnIntegral ? turnIntegral = 0 : turnIntegral += turnError;

        /*****************************TURN DERIVATIVE*****************************/
        // turnDerivative = turnError - previousTurnError;

        // Calculate the power for each of the motors
        turnPower = (turnError * turnkP) + (turnDerivative * turnkD);

        // cout << "Turn error: " << turnError << endl;
        // cout << "Turn power: " << turnPower << endl;
        // cout << "Inertial heading: " << Inertial.heading(deg) << endl;

        // Make the motors spin
        Right.spin(vex::directionType::rev, turnPower, vex::voltageUnits::volt);
        Left.spin(vex::directionType::fwd, -turnPower, vex::voltageUnits::volt);

        previousTurnError = turnError;

        wait(dT, vex::timeUnits::msec);
    }

    cout << "Done turning" << endl;
}

/// @brief This method gets the robot to just drive straight, but it doesn't use a PID so it goes quite fast and is used for shorter distances that don't require a lot of accuracy
/// @param drive_distance is how far you want the robot to drive
/// @param speed is the speed at which you want the robot to drive
/// @return Void
void PID::drive_straight(float drive_distance, float speed)
{
    // Get how many degrees the left side and right side motors have to turn
    float drive_degrees = Inches_To_Degrees(drive_distance);

    // Spin the motors
    Left.spinFor(vex::directionType::fwd, -drive_degrees, vex::rotationUnits::deg, speed, vex::velocityUnits::pct, false);
    Right.spinFor(vex::directionType::rev, -drive_degrees, vex::rotationUnits::deg, speed, vex::velocityUnits::pct);
}