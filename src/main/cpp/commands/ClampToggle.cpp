#include "commands/ClampToggle.h" // relevent header file

ClampToggle::ClampToggle(robotArm* robotArm) : m_robotArm{robotArm} {  // constructor for command class
    SetName("ClampToggle"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ClampToggle::Initialize() { printf("ClampToggle Initialized \n"); } // print debug message on initialization

void ClampToggle::Execute() { // on command call (button press)
    m_robotArm->clampToggle(); // make m_robotArm point to the ClampToggle() command
}

bool ClampToggle::IsFinished() { return true; } // return when ??