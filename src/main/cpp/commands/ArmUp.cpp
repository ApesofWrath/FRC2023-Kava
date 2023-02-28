#include "commands/ArmUp.h" // relevent header file

ArmUp::ArmUp(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ArmUp"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ArmUp::Initialize() { printf("ArmUp Initialized \n"); } // print debug message on initialization

void ArmUp::Execute() { // ??[when does it do this]
    m_robotArm->armUp(); // make m_robotArm point to the armDown() command
}

bool ArmUp::IsFinished() { return true; } // return when ??