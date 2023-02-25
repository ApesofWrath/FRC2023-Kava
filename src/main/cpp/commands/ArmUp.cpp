#include "commands/ArmUp.h"

ArmUp::ArmUp(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ArmUp");
    AddRequirements({m_robotArm});
}

void ArmUp::Initialize() { printf("ArmUp Initialized \n"); }

void ArmUp::Execute() {
    m_robotArm->armUp();
}

bool ArmUp::IsFinished() { return true; }