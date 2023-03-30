#include "commands/ScoreHighPreload.h" // relevent header file

ScoreHighPreload::ScoreHighPreload(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ScoreHighPreload"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
}

void ScoreHighPreload::Initialize() { printf("ScoreHighPreload Initialized \n"); } // print debug message on initialization

void ScoreHighPreload::Execute() { // on command call (button press)
    frc2::SequentialCommandGroup(
    frc2::InstantCommand([this] {m_robotArm->scoreHigh();}), 
    frc2::WaitCommand(3.0_s),
    frc2::InstantCommand([this] {m_robotArm->clampToggle();}),
    frc2::WaitCommand(0.5_s),
    frc2::InstantCommand([this] {m_robotArm->armUp();})
    ); // make m_robotArm point to the scoreHigh() command
}

bool ScoreHighPreload::IsFinished() { return true; } // return when ??