#include "commands/TeleOutLow.h" // relevent header file

TeleOutLow::TeleOutLow(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("TeleOutLow"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void TeleOutLow::Initialize() { printf("TeleOutLow Initialized \n"); } // print debug message on initialization

void TeleOutLow::Execute() { // on command call (button press)
    m_robotArm->teleOutLong(); // make m_robotArm point to the teleOutLong() command
}

bool TeleOutLow::IsFinished() { return true; } // return when ??