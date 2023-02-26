#include "commands/ClampOpen.h"

ClampOpen::ClampOpen(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ClampOpen");
    AddRequirements({m_robotArm});
}

void ClampOpen::Initialize() { printf("ClampOpen Initialized \n"); }

void ClampOpen::Execute() {
    m_robotArm->clampOpen();
}

bool ClampOpen::IsFinished() { return true; }