#include "commands/ScoreMid.h" // relevent header file

ScoreMid::ScoreMid(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ScoreMid"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ScoreMid::Initialize() { printf("ScoreMid Initialized \n"); } // print debug message on initialization

void ScoreMid::Execute() { // on command call (button press)
    m_robotArm->scoreMid(); // make m_robotArm point to the scoreLow() command
}

bool ScoreMid::IsFinished() { return true; } // return when ??