#include "commands/TeleIn.h" // relevent header file

TeleIn::TeleIn(robotArm* robotArm) : m_robotArm{robotArm} {  // constructor for command class
    SetName("TeleIn"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void TeleIn::Initialize() { printf("TeleIn Initialized \n"); } // print debug message on initialization

void TeleIn::Execute() { // ??[when does it do this]
    m_robotArm->teleIn(); // make m_robotArm point to the armDown() command
}

bool TeleIn::IsFinished() { return true; } // return when ??