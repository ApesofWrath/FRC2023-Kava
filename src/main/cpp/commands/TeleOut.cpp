#include "commands/TeleOut.h"

TeleOut::TeleOut(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("TeleOut");
    AddRequirements({m_robotArm});
}

void TeleOut::Initialize() { printf("TeleOut Initialized \n"); }

void TeleOut::Execute() {
    m_robotArm->teleOut();
}

bool TeleOut::IsFinished() { return true; }