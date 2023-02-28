#include "commands/ClampClose.h" // relevent header file

ClampClose::ClampClose(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ClampClose"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ClampClose::Initialize() { printf("ClampClose Initialized \n"); } // print debug message on initialization

void ClampClose::Execute() { // on command call (button press)
    m_robotArm->clampClose(); // make m_robotArm point to the clampClose() command
}

bool ClampClose::IsFinished() { return true; } // return when ??