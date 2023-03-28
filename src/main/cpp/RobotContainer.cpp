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
#include "commands/ZeroGyro.h"
#include "commands/NormalSpeed.h"
#include "commands/SlowDown.h"

// Default drivetrain command for swerve
RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Configure the button bindings
  ConfigureButtonBindings();

  // $ CONTROLLER INPUTS FOR SWERVE DRIVE BELOW
  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return (MathFunctions::joystickCurve(m_controllerMain.GetX(), controllerConstants::kControllerCurve)); },
    [this] { return (MathFunctions::joystickCurve(m_controllerMain.GetY(), controllerConstants::kControllerCurve)); },
    [this] { return (m_controllerMain.GetRawAxis(4)); })); 
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

  // Zeroing for swervedrive command
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kStart).OnTrue(ZeroGyro(&m_drivetrain).ToPtr());

  // Slow button for swerve (whenever left OR right bumper is held down), slows swerve to 25% of original speed
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kRightBumper).OnTrue(SlowDown(&m_drivetrain).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kRightBumper).OnFalse(NormalSpeed(&m_drivetrain).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kLeftBumper).OnTrue(SlowDown(&m_drivetrain).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kLeftBumper).OnFalse(NormalSpeed(&m_drivetrain).ToPtr());

  // Robot arm commands
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kRightBumper).OnTrue(ClampToggle(&m_robotArm).ToPtr());
  
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kY).OnTrue(ScoreHigh(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kX).OnTrue(ScoreMid(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kA).OnTrue(ScoreLow(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kB).OnTrue(GrabCode(&m_robotArm).ToPtr());

  // Zeroing commands
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kStart).OnTrue(ZeroAngle(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kLeftBumper).OnTrue(ArmUp(&m_robotArm).ToPtr());

  // frc::SmartDashboard::PutData(&m_chooser);
}

// Command autons are made here
frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous

  return &m_Auto;
}