#include "commands/ClampOpen.h" // relevent header file

ClampOpen::ClampOpen(robotArm* robotArm) : m_robotArm{robotArm} {  // constructor for command class
    SetName("ClampOpen"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ClampOpen::Initialize() { printf("ClampOpen Initialized \n"); } // print debug message on initialization

void ClampOpen::Execute() { // on command call (button press)
    m_robotArm->clampOpen(); // make m_robotArm point to the clampOpen() command
}

bool ClampOpen::IsFinished() { return true; } // return when ??