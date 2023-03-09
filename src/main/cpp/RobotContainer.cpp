// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  // Initialize buttonA, buttonB and buttonY Events
  frc2::JoystickButton buttonA{&m_controllerMain, 1};
  frc2::JoystickButton buttonB{&m_controllerMain, 2};
  frc2::JoystickButton buttonY{&m_controllerMain, 3}; 
  //Bind Limelight Pipeline 0 (Apriltags) and Pipeline 1 (Retroreflective) to ButtonA and ButtonB events respectively
  buttonA.WhenPressed(frc2::InstantCommand([this] { m_vision.SelectPipeline(0); }));
  buttonB.WhenPressed(frc2::InstantCommand([this] { m_vision.SelectPipeline(1); }));
  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return MathFunctions::joystickCurve(m_controllerMain.GetX(), 8.0); },
    [this] { return MathFunctions::joystickCurve(m_controllerMain.GetY(), 8.0); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 
}

void RobotContainer::ConfigureButtonBindings() {
   frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kY).WhileTrue(PointAtTarget(&m_drivetrain, &m_vision).ToPtr());
   frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kX).WhileTrue(Align(&m_drivetrain, &m_vision).ToPtr());

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_Auto;
}
