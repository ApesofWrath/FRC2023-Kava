#include "commands/ArmDown.h"

ArmDown::ArmDown(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ArmDown");
    AddRequirements({m_robotArm});
}

void ArmDown::Initialize() { printf("ArmDown Initialized \n"); }

void ArmDown::Execute() {
    m_robotArm->armDown();
}

bool ArmDown::IsFinished() { return true; }