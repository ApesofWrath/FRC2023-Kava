// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() :
m_autoBuilder{
    [this]() { return m_drivetrain.GetOdometry(); }, // Function to supply current robot pose
    [this](auto initPose) { m_drivetrain.ResetOdometry(initPose); }, // Function used to reset odometry at the beginning of auto
    pathplanner::PIDConstants(0.000009, 0.0, 0.0), // PID constants to correct for translation error (used to create the X and Y PID controllers)
    pathplanner::PIDConstants(0.0000006, 0.0, 0.0), // PID constants to correct for rotation error (used to create the rotation controller)
    [this](frc::ChassisSpeeds speeds) {m_drivetrain.SwerveDrive(speeds.vx, speeds.vy, speeds.omega, true);}, // Output function that accepts field relative ChassisSpeeds
    eventMap,
    { &m_drivetrain }, // Drive requirements, usually just a single drive subsystem
    true // Should the path be automatically mirrored depending on alliance color. Optional, defaults to true
}
 {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return m_controllerMain.GetX(); },
    [this] { return m_controllerMain.GetY(); },
    [this] { return m_controllerMain.GetRawAxis(4); })); 

    m_chooser.SetDefaultOption("DoNothing", "DoNothing");
    m_chooser.AddOption("StraightLineTestX", "StraightLineTestX");
    m_chooser.AddOption("StraightLineTestY", "StraightLineTestY");
    m_chooser.AddOption("CurvedLineTest", "CurvedLineTest");
    m_chooser.AddOption("BumpcubeBalance", "BumpcubeBalance");
    frc::SmartDashboard::PutData(&m_chooser);
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  if (m_chooser.GetSelected() == "DoNothing")
  {
    return frc2::WaitCommand(15_s).ToPtr();
  }
  else
  {
    std::vector<pathplanner::PathPlannerTrajectory> pathGroup = pathplanner::PathPlanner::loadPathGroup(m_chooser.GetSelected(), {pathplanner::PathConstraints(4_mps, 3_mps_sq)});
    frc2::CommandPtr fullAuto = m_autoBuilder.fullAuto(pathGroup);
    frc2::CommandPtr fullAutoReqDrive = std::move(fullAuto).AlongWith(std::move(RequireDrive(&m_drivetrain).ToPtr()));
    return std::move(fullAutoReqDrive).AndThen(std::move(Drive(&m_drivetrain, 0, 0, 0).ToPtr()));
  }
  
  /* if (path == "AutonTest")
  {
    return new Drive(&m_drivetrain, 1_mps, 1_mps, 15_deg_per_s);
  } */
  //return &m_Auto;
}
