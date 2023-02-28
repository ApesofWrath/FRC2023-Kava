#include "commands/ArmDownLow.h" // relevent header file

ArmDownLow::ArmDownLow(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ArmDownLow"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ArmDownLow::Initialize() { printf("ArmDownLow Initialized \n"); } // print debug message on initialization

void ArmDownLow::Execute() { // ??[when does it do this]
    m_robotArm->armDownLow(); // make m_robotArm point to the armDown() command
}

bool ArmDownLow::IsFinished() { return true; } // return when ??