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
  if(m_controllerMain.GetRawButton(4)){ // is Y pressed? arm up!
    robotArm::armUp();
  }
  if(m_controllerMain.GetRawButton(2)){ // is B pressed? arm down!
    robotArm::armDown();
  }
  if(m_controllerMain.GetRawButton(1)){ // is A pressed? secret 3rd thing!
  }
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}
