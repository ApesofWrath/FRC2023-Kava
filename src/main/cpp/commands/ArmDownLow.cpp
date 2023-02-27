#include "commands/ArmDownLow.h"

ArmDownLow::ArmDownLow(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ArmDownLow");
    AddRequirements({m_robotArm});
}

void ArmDownLow::Initialize() { printf("ArmDownLow Initialized \n"); }

void ArmDownLow::Execute() {
    m_robotArm->armDownLow();
}

bool ArmDownLow::IsFinished() { return true; }