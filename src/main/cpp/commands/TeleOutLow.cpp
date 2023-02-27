#include "commands/TeleOutLow.h"

TeleOutLow::TeleOutLow(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("TeleOutLow");
    AddRequirements({m_robotArm});
}

void TeleOutLow::Initialize() { printf("TeleOutLow Initialized \n"); }

void TeleOutLow::Execute() {
    m_robotArm->teleOutLong();
}

bool TeleOutLow::IsFinished() { return true; }