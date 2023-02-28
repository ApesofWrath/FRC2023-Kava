#include "commands/TeleIn.h" // relevent header file

TeleIn::TeleIn(robotArm* robotArm) : m_robotArm{robotArm} {  // constructor for command class
    SetName("TeleIn"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void TeleIn::Initialize() { printf("TeleIn Initialized \n"); } // print debug message on initialization

void TeleIn::Execute() { // on command call (button press)
    m_robotArm->teleIn(); // make m_robotArm point to the teleIn() command
}

bool TeleIn::IsFinished() { return true; } // return when ??