#include "RobotController.h"

static ControlMode currentMode = MODE_MANUAL;

namespace RobotController
{
    void setMode(ControlMode mode)
    {
        currentMode = mode;
    }

    ControlMode getMode()
    {
        return currentMode;
    }
}