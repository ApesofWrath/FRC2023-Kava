#include "commands/ArmDown.h"

ArmDown::ArmDown(robotArm* subsystem) : m_arm(subsystem) {
    AddRequirements(subsystem);
}

void ArmDown::Initialize() {
    m_arm->armDown();
}

bool ArmDown::IsFinished() {
    return true;
}