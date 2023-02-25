#include "commands/TeleIn.h"

TeleIn::TeleIn(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("TeleIn");
    AddRequirements({m_robotArm});
}

void TeleIn::Initialize() { printf("TeleIn Initialized \n"); }

void TeleIn::Execute() {
    m_robotArm->teleIn();
}

bool TeleIn::IsFinished() { return true; }