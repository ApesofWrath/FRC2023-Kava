#include "commands/Arm/GrabCone.h" // relevent header file

GrabCone::GrabCone(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("GrabCone"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void GrabCone::Initialize() { printf("GrabCone Initialized \n"); } // print debug message on initialization

void GrabCone::Execute() { // on command call (button press)
    m_robotArm->grabCone(); // make m_robotArm point to the scoreLow() command
}

bool GrabCone::IsFinished() { return true; } // return when ??