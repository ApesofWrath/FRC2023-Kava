// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_Auto(&m_drivetrain) {
  // Initialize all of your commands and subsystems here

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
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  /*using namespace pathplanner;
  std::vector<PathPlannerTrajectory> pathGroup = PathPlanner::loadPathGroup("New Path", {PathConstraints(4_mps, 3_mps_sq)});
  SwerveAutoBuilder autoBuilder(
    [this]() { return swerveModule::GetPosition(); }, // Function to supply current robot pose
    [this](auto initPose) { swerveSubsystem.resetPose(initPose); }, // Function used to reset odometry at the beginning of auto
    PIDConstants(5.0, 0.0, 0.0), // PID constants to correct for translation error (used to create the X and Y PID controllers)
    PIDConstants(0.5, 0.0, 0.0), // PID constants to correct for rotation error (used to create the rotation controller)
    [this](auto speeds) { swerveSubsystem.driveFieldRelative(speeds); }, // Output function that accepts field relative ChassisSpeeds // Our event map
    { &drivetrain, &swerveModule }, // Drive requirements, usually just a single drive subsystem
    true
  );*/
  return &m_Auto;

}
