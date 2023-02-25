// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include "commands/ArmDown.h"
#include "commands/ArmUp.h"

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  /* m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return m_controller.GetRawAxis(0); }, // m_controllerMain.GetX()
    [this] { return m_controller.GetRawAxis(1); }, // m_controllerMain.GetY()
    [this] { return m_controller.GetRawAxis(4); })); */ // m_controllerMain.GetRawAxis(4)
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kB).OnTrue(ArmDown(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controller, frc::XboxController::Button::kY).OnTrue(ArmUp(&m_robotArm).ToPtr());
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}