#include "commands/Arm/ScoreLow.h" // relevent header file

ScoreLow::ScoreLow(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ScoreLow"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ScoreLow::Initialize() { printf("ScoreLow Initialized \n"); } // print debug message on initialization

void ScoreLow::Execute() { // on command call (button press)
    m_robotArm->scoreLow(); // make m_robotArm point to the scoreLow() command
}

bool ScoreLow::IsFinished() { return true; } // return when ??