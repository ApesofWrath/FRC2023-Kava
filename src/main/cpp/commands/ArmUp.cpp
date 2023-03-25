#include "commands/ArmUp.h" // relevent header file

// Constructor for command, takes in pointer to subsystem and sets the name of the command, etc
ArmUp::ArmUp(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ArmUp"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

// When the command is first run, prints
void ArmUp::Initialize() { printf("ArmUp Initialized \n"); } // print debug message on initialization

// When command is run, after Initialize is run, runs the armUp() function part of the robotArm subsystem
void ArmUp::Execute() { // on command call (button press)
    m_robotArm->armUp(); // make m_robotArm point to the armUp() command
}

// When command is finished, return true to state command is finished
bool ArmUp::IsFinished() { return true; } // return when ??