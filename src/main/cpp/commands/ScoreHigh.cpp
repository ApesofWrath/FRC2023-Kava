#include "commands/ScoreHigh.h"

ScoreHigh::ScoreHigh(robotArm* robotArm) : m_robotArm{robotArm} {
    SetName("ScoreHigh");
    AddRequirements({m_robotArm});
}

void ScoreHigh::Initialize() { printf("ScoreHigh Initialized \n"); }

void ScoreHigh::Execute() {
    m_robotArm->scoreHigh();
}

bool ScoreHigh::IsFinished() { return true; }