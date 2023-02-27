#include "commands/ScoreLow.h"

ScoreLow::ScoreLow(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ScoreLow");
    AddRequirements({m_robotArm});
}

void ScoreLow::Initialize() { printf("ScoreLow Initialized \n"); }

void ScoreLow::Execute() {
    m_robotArm->scoreLow();
}

bool ScoreLow::IsFinished() { return true; }