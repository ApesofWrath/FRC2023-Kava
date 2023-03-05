// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>
#include "Constants.h"
#include <pathplanner/lib/auto/SwerveAutoBuilder.h>
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/PIDConstants.h>
#include "commands/Auto.h"
#include "commands/Drive.h"
#include "subsystems/drivetrain.h"

#include <frc/Joystick.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();
  
  frc2::Command* GetAutonomousCommand();
 private:
  // The robot's subsystems and commands are defined here...
  drivetrain m_drivetrain;
  Auto m_Auto;
<<<<<<< HEAD
  //pathplanner::SwerveAutoBuilder m_autoBuilder;
  /* std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;
  frc::SendableChooser<std::string> m_chooser; */
=======
  pathplanner::SwerveAutoBuilder m_autoBuilder;
  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;
  frc::SendableChooser<std::string> m_chooser;
>>>>>>> 3b9d68b (make auton build)
  void ConfigureButtonBindings();

  frc::Joystick m_controllerMain{controllerConstants::kControllerMainID};
};
