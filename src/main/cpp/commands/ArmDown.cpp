#include "commands/ArmDown.h"// relevent header file

ArmDown::ArmDown(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ArmDown"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ArmDown::Initialize() { printf("ArmDown Initialized \n"); } // print debug message on initialization

void ArmDown::Execute() { // on command call (button press)
    m_robotArm->armDown(); // make m_robotArm point to the armDown() command
}

bool ArmDown::IsFinished() { return true; } // return when ??