#include "vex.h"
#include "../Odometry/Odometry.h"

using namespace vex;

class PID
{
public:
    /// @brief This method will move the robot to a position on the field
    /// @param The x position that you want the robot to move to on the field
    /// @param The y position that you want the robot to move to on the field
    /// @param The angle at which you want the robot to be at once it is done moving
    /// @param Whether the x and y values are based off of the assumption that the robot is always starting at point (0, 0)
    void MoveToPoint(double targetX, double targetY, double targetTheta = NULL, bool isRelativeToZero = false)
    {
        // The total power for turning and moving forward
        double power = 0;
        double turnPower = 0;

        // The errors both while moving forward and turning
        double error = 10;
        double turnError;

        // Constants
        float kP = 0.01;
        float turnkP = 0.01;

        if (!isRelativeToZero)
        {
            while (error >= 3 || (error < 0 && error >= -3))
            {
                        }
        }
    }

    /// @brief This method will turn the robot to a certain angle relative to the field
    /// @param This is the angle at which you want the robot to turn to
    void Turn(double targetTheta)
    {
    }
};