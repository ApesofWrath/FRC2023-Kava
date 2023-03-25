// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include "commands/ArmUp.h"
#include "commands/ClampToggle.h"
#include "commands/ScoreHigh.h"
#include "commands/ScoreMid.h"
#include "commands/ScoreLow.h"
#include "commands/ZeroAngle.h"
#include "commands/GrabCone.h"

// Default drivetrain command for swerve
RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Configure the button bindings
  ConfigureButtonBindings();

  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return MathFunctions::joystickCurve(m_controllerMain.GetX(), controllerConstants::kControllerCurve); },
    [this] { return MathFunctions::joystickCurve(m_controllerMain.GetY(), controllerConstants::kControllerCurve); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 
}

// All the button commands are set in this function
void RobotContainer::ConfigureButtonBindings() {
  //** For commented command file, look at:
  //** ArmUp.cpp and
  //** ArmUp.h

  //Bind Limelight Pipeline 0 (Apriltags) and Pipeline 1 (Retroreflective) to ButtonA and ButtonB events respectively
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kA).WhileTrue(frc2::InstantCommand([this] { m_vision.SelectPipeline(0); }).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kB).WhileTrue(frc2::InstantCommand([this] { m_vision.SelectPipeline(1); }).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kY).WhileTrue(PointAtTarget(&m_drivetrain, &m_vision).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kX).WhileTrue(Align(&m_drivetrain, &m_vision).ToPtr());

  // Robot arm commands
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kRightBumper).OnTrue(ClampToggle(&m_robotArm).ToPtr());
  
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kY).OnTrue(ScoreHigh(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kX).OnTrue(ScoreMid(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kA).OnTrue(ScoreLow(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kB).OnTrue(GrabCode(&m_robotArm).ToPtr());

  // Zeroing commands
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kStart).OnTrue(ZeroAngle(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kLeftBumper).OnTrue(ArmUp(&m_robotArm).ToPtr());

  // Chooser for command auton
  m_chooser.SetDefaultOption("ScoreHigh", "ScoreHigh");
  m_chooser.AddOption("DriveBack", "DriveBack");

  frc::SmartDashboard::PutData(&m_chooser);
}

// Command autons are made here
frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  if (m_chooser.GetSelected() == "ScoreHigh")
  {
    return std::move(std::move(std::move(ClampToggle(&m_robotArm).ToPtr()).AndThen(std::move(ScoreHigh(&m_robotArm).ToPtr()))).AndThen(std::move(ClampToggle(&m_robotArm).ToPtr()))).AndThen(std::move(ArmUp(&m_robotArm).ToPtr()));
  }
  /* if (m_chooser.GetSelected() == "DoNothing")
  {
    return 
  } */
}