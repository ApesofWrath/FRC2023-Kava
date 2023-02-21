// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here
  ConfigureButtonBindings();

  // Configure the button bindings
  ConfigureButtonBindings();

  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return m_controllerMain.GetX(); },
    [this] { return m_controllerMain.GetY(); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  m_controllerMain.Y().OnTrue(frc2::cmd::RunOnce(
      [this] {
        m_arm.SetGoal(2_rad);
        m_arm.Enable();
      },
      {&m_arm}));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}
