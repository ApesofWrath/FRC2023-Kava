#include "commands/ClampClose.h"

ClampClose::ClampClose(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ClampClose");
    AddRequirements({m_robotArm});
}

void ClampClose::Initialize() { printf("ClampClose Initialized \n"); }

void ClampClose::Execute() {
    m_robotArm->clampClose();
}

bool ClampClose::IsFinished() { return true; }