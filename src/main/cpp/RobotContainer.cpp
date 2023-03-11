// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include "commands/ArmDown.h"
#include "commands/ArmUp.h"
#include "commands/TeleIn.h"
#include "commands/TeleOut.h"
#include "commands/ClampClose.h"
#include "commands/ClampOpen.h"
#include "commands/TeleOutLow.h"
#include "commands/ArmDownLow.h"
#include "commands/ScoreHigh.h"
#include "commands/ScoreLow.h"

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
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kLeftStick).OnTrue(ScoreHigh(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kRightStick).OnTrue(ScoreLow(&m_robotArm).ToPtr());

  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kB).OnTrue(ArmDown(&m_robotArm).ToPtr());

  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kY).OnTrue(ArmUp(&m_robotArm).ToPtr());

  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kX).OnTrue(TeleOut(&m_robotArm).ToPtr());

  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kA).OnTrue(TeleIn(&m_robotArm).ToPtr());

  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kRightBumper).OnTrue(ClampClose(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kLeftBumper).OnTrue(ClampOpen(&m_robotArm).ToPtr());

  // manual zeros
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kBack).OnTrue(TeleOutLow(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kStart).OnTrue(ArmDownLow(&m_robotArm).ToPtr());
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}