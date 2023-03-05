// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "MathFunctions.h"

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  frc2::JoystickButton button{&m_controllerMain, 1}; // Replace "1" with the button number you want to bind the command to
  button.WhenPressed(m_vision.SelectPipeline(1));
  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return MathFunctions::joystickCurve(m_controllerMain.GetX(), 5.0); },
    [this] { return MathFunctions::joystickCurve(m_controllerMain.GetY(), 5.0); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 

}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}
