// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "subsystems/vision.h"

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return m_controllerMain.GetX(); },
    [this] { return m_controllerMain.GetY(); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 
  Vision visionsubsystem;
  frc2::Trigger apriltagPipelineSwitchTrigger([&, this] { return m_controllerMain.GetRawButtonPressed(1); });
  apriltagPipelineSwitchTrigger.WhenActive([&, this] { visionsubsystem.SelectPipeline(0); });
  frc2::Trigger retroreflectivePipelineSwitchTrigger([&, this] { return m_controllerMain.GetRawButtonPressed(2); });
  retroreflectivePipelineSwitchTrigger.WhenActive([&, this] { visionsubsystem.SelectPipeline(1); });

}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}
