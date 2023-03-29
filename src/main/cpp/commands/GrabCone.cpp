#include "commands/GrabCone.h" // relevent header file

GrabCode::GrabCode(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("GrabCode"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void GrabCode::Initialize() { printf("GrabCode Initialized \n"); } // print debug message on initialization

void GrabCode::Execute() { // on command call (button press)
    m_robotArm->grabCone(); // make m_robotArm point to the scoreLow() command
}

bool GrabCode::IsFinished() { return true; } // return when ??