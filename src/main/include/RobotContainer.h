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
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/WaitCommand.h>
#include "Constants.h"
#include "commands/Drive.h"
#include "commands/PointAtTarget.h"
#include "commands/Align.h"
#include "subsystems/drivetrain.h"
#include "subsystems/vision.h"
#include "MathFunctions.h"
#include "subsystems/robotArm.h"

#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/Commands.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/Joystick.h>
#include <frc2/Command/Button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>

#include "commands/RequireDrive.h"
#include "commands/AutoBalance.h"
#include "commands/RequireDrive.h"
#include "subsystems/drivetrain.h"
#include <pathplanner/lib/auto/SwerveAutoBuilder.h>
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/PIDConstants.h>
#include <frc/Joystick.h>
#include <frc2/Command/Button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>

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
  pathplanner::SwerveAutoBuilder m_autoBuilder;
  std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap = 
  {{"AutoBalance", std::make_shared<AutoBalance>(&m_drivetrain)},
  {"event", std::make_shared<frc2::PrintCommand>("path end")}};
  void ConfigureButtonBindings();

  // Controller creation
  frc::Joystick m_controllerMain{controllerConstants::kControllerMainID};
  frc2::CommandXboxController m_controllerOperator{controllerConstants::kControllerAuxID};
};
