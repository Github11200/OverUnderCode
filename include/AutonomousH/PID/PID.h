#include "vex.h"

using namespace vex;

class PID {
public:
    /// @brief This method will move the robot to a position on the field
    /// @param The x position that you want the robot to move to on the field
    /// @param The y position that you want the robot to move to on the field
    /// @param The angle at which you want the robot to be at once it is done moving
    void MoveToPoint(double x,  double y, double targetTheta = NULL) {
    }

    /// @brief This method will turn the robot to a certain angle relative to the field
    /// @param This is the angle at which you want the robot to turn to
    void Turn(double targetTheta) {
    }
};