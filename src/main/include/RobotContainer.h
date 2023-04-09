// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/PrintCommand.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandPtr.h>

#include "Constants.h"
#include "commands/Drivetrain/Drive.h"
#include "commands/Vision/PointAtTarget.h"
#include "commands/Vision/Align.h"
#include "commands/ScoreHighPreload.h"
#include "commands/ScoreMidPreload.h"
#include "subsystems/drivetrain.h"
#include "subsystems/vision.h"
#include "MathFunctions.h"
#include "subsystems/robotArm.h"

#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/Commands.h>
#include <frc2/command/InstantCommand.h>

#include <frc/Joystick.h>
#include <frc2/Command/Button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>

#include "commands/RequireDrive.h"
#include "commands/AutoBalance.h"
#include "commands/RequireDrive.h"
#include <pathplanner/lib/auto/SwerveAutoBuilder.h>
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/PIDConstants.h>

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
  
  frc2::CommandPtr GetAutonomousCommand();
 private:
  // The robot's subsystems and commands are defined here...
  drivetrain m_drivetrain;
  Vision m_vision;
  robotArm m_robotArm;

  frc::SendableChooser<std::string> m_chooser;
  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap = 
  {{"AutoBalance", std::make_shared<AutoBalance>(&m_drivetrain)},
  {"ScoreHighPreload", std::make_shared<ScoreHighPreload>(&m_robotArm)},
  {"ScoreMidPreload", std::make_shared<ScoreMidPreload>(&m_robotArm)}
  };
  pathplanner::SwerveAutoBuilder m_autoBuilder;
  void ConfigureButtonBindings();

  // Controller creation
  frc::Joystick m_controllerMain{controllerConstants::kControllerMainID};
  frc2::CommandXboxController m_controllerOperator{controllerConstants::kControllerAuxID};
};
