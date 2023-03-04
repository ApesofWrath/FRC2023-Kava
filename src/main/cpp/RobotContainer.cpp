// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() : 
m_Auto(&m_drivetrain)/* ,
m_autoBuilder(
  [this]() { return m_drivetrain.GetOdometry(); }, // Function to supply current robot pose
  [this](auto initPose) { m_drivetrain.ResetOdometry(initPose); }, // Function used to reset odometry at the beginning of auto
  pathplanner::PIDConstants(5.0, 0.0, 0.0), // PID constants to correct for translation error (used to create the X and Y PID controllers)
  pathplanner::PIDConstants(0.5, 0.0, 0.0), // PID constants to correct for rotation error (used to create the rotation controller)
  [this](auto speeds) { new Drive(&m_drivetrain, speeds.vx, speeds.vy, speeds.omega); }, // Output function that accepts field relative ChassisSpeeds
  eventMap,
  { &m_drivetrain }, // Drive requirements, usually just a single drive subsystem
  true // Should the path be automatically mirrored depending on alliance color. Optional, defaults to true
) */
{
  // Initialize all of your commands and subsystems here
  // Configure the button bindings
  ConfigureButtonBindings();

  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return m_controllerMain.GetX(); },
    [this] { return m_controllerMain.GetY(); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 

    /* m_chooser.SetDefaultOption("StraightLineTest", "StraightLineTest");
    m_chooser.AddOption("CurvedLineTest", "CurvedLineTest");
    m_chooser.AddOption("AutonTest", "AutonTest"); */
    //frc::SmartDashboard::PutString("Auto Choice", m_chooser.GetSelected());
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  /* std::string path = m_chooser.GetSelected();
  using namespace pathplanner;
  std::vector<PathPlannerTrajectory> pathGroup = PathPlanner::loadPathGroup(path, {PathConstraints(4_mps, 3_mps_sq)});
  frc2::Command* fullAuto =  m_autoBuilder.fullAuto(pathGroup);
  return fullAuto; */
  return &m_Auto;

}
