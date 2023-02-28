#include "commands/ScoreHigh.h" // relevent header file

ScoreHigh::ScoreHigh(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ScoreHigh"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ScoreHigh::Initialize() { printf("ScoreHigh Initialized \n"); } // print debug message on initialization

void ScoreHigh::Execute() { // ??[when does it do this]
    m_robotArm->scoreHigh(); // make m_robotArm point to the armDown() command
}

bool ScoreHigh::IsFinished() { return true; } // return when ??