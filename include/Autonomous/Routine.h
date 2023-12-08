#ifndef ROUTINE_H
#define ROUTINE_H

#include "vex.h"
#include "../../include/Autonomous/PID.h"

using namespace vex;

/// @brief This function just calibrates the inertial sensor
void CalibrateInertial();

/// @brief This function contains the code for the skills routine
void Skills();

/// @brief This function contains the code for the far side autonomous routine
void FarSideAutonomous();

/// @brief This function contains the code for the close side routine
void CloseSideAutonomous();

#endif