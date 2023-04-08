#include "commands/Arm/ZeroAngle.h" // relevent header file

ZeroAngle::ZeroAngle(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ZeroAngle"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ZeroAngle::Initialize() { printf("ZeroAngle Initialized \n"); } // print debug message on initialization

void ZeroAngle::Execute() { // on command call (button press)
    m_robotArm->angleManualZero(); // make m_robotArm point to the scoreLow() command
}

bool ZeroAngle::IsFinished() { return true; } // return when ??