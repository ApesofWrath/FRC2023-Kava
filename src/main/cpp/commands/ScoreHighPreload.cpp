#include "commands/ScoreHighPreload.h" // relevent header file
#include "commands/Arm/ClampToggle.h"
#include "commands/Arm/ScoreHigh.h"
#include "commands/Arm/ArmUp.h"
ScoreHighPreload::ScoreHighPreload(robotArm* robotArm) : m_robotArm{robotArm} { // constructor for command class
    SetName("ScoreHighPreload"); // set the ?? name
    AddRequirements({m_robotArm}); // require the m_robotArm pointer
    AddCommands(
        ClampToggle(m_robotArm),
        frc2::WaitCommand(3.0_s),
        ScoreHigh(m_robotArm),
        frc2::WaitCommand(2.5_s),
        ClampToggle(m_robotArm),
        frc2::WaitCommand(0.5_s),
        ArmUp(m_robotArm)
        //frc2::InstantCommand([this](){ new ; }),
        // frc2::WaitCommand(2.0_s),
        // frc2::InstantCommand([this] {m_robotArm->clampToggle();}),
        // frc2::WaitCommand(0.5_s),
        // frc2::InstantCommand([this] {m_robotArm->armUp();}),
    );
}

//void ScoreMidPreload::Initialize() { printf("ScoreMidPreload Initialized \n"); } // print debug message on initialization

/*void ScoreMidPreload::Execute() { // on command call (button press)
    frc2::SequentialCommandGroup(
    frc2::InstantCommand([this] {m_robotArm->scoreMid();}), 
    frc2::WaitCommand(2.0_s),
    frc2::InstantCommand([this] {m_robotArm->clampToggle();}),
    frc2::WaitCommand(0.5_s),
    frc2::InstantCommand([this] {m_robotArm->armUp();})
    ); // make m_robotArm point to the scoreHigh() command
}*/

//bool ScoreMidPreload::IsFinished() { return true; } // return when ??