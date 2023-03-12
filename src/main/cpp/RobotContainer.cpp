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

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return m_controllerMain.GetX(); }, // m_controllerMain.GetX()
    [this] { return m_controllerMain.GetY(); }, // m_controllerMain.GetY()
    [this] { return m_controllerMain.GetRawAxis(4); })); // m_controllerMain.GetRawAxis(4)
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  // frc2::JoystickButton(&m_controller, frc::XboxController::Button::kRightBumper).OnTrue(ClampClose(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kRightBumper).OnTrue(ClampToggle(&m_robotArm).ToPtr());

  // all scoring positons
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kY).OnTrue(ScoreHigh(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kX).OnTrue(ScoreMid(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kA).OnTrue(ScoreLow(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kB).OnTrue(GrabCode(&m_robotArm).ToPtr());

  // zeroing
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kStart).OnTrue(ZeroAngle(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kLeftBumper).OnTrue(ArmUp(&m_robotArm).ToPtr());
  // frc2::JoystickButton(&m_controller, frc::XboxController::Button::kLeftStick).OnTrue(ArmUp(&m_robotArm).ToPtr());
  // frc2::JoystickButton(&m_controller, frc::XboxController::Button::kRightStick).OnTrue(TeleIn(&m_robotArm).ToPtr());

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}