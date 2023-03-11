#include "commands/TeleOut.h" // relevent header file

TeleOut::TeleOut(robotArm* robotArm) : m_robotArm{robotArm} {  // constructor for command class
    SetName("TeleOut"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void TeleOut::Initialize() { printf("TeleOut Initialized \n"); } // print debug message on initialization

void TeleOut::Execute() { // on command call (button press)
    m_robotArm->grabCone(); // make m_robotArm point to the teleOut() command
}

bool TeleOut::IsFinished() { return true; } // return when ??