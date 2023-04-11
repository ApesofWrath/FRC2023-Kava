// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include "commands/Arm/ArmUp.h"
#include "commands/Arm/ClampToggle.h"
#include "commands/Arm/ScoreHigh.h"
#include "commands/Arm/ScoreMid.h"
#include "commands/Arm/ScoreLow.h"
#include "commands/Arm/ZeroAngle.h"
#include "commands/Arm/GrabCone.h"
#include "commands/Drivetrain/ZeroGyro.h"
#include "commands/Drivetrain/NormalSpeed.h"
#include "commands/Drivetrain/SlowDown.h"

RobotContainer::RobotContainer() :
m_autoBuilder{
    [this]() { return m_drivetrain.GetOdometry(); }, // Function to supply current robot pose
    [this](auto initPose) { m_drivetrain.ResetOdometry(initPose); }, // Function used to reset odometry at the beginning of auto
    pathplanner::PIDConstants(3.0, 0.0, 0.0), // PID constants to correct for translation error (used to create the X and Y PID controllers)
    pathplanner::PIDConstants(0.025, 0.0, 0.0), // PID constants to correct for rotation error (used to create the rotation controller)
    [this](frc::ChassisSpeeds speeds) {m_drivetrain.SwerveDrive(speeds.vx, speeds.vy, speeds.omega, true);}, // Output function that accepts field relative ChassisSpeeds
    eventMap,
    { &m_drivetrain }, // Drive requirements, usually just a single drive subsystem
    true // Should the path be automatically mirrored depending on alliance color. Optional, defaults to true
}
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // $ CONTROLLER INPUTS FOR SWERVE DRIVE BELOW
  m_drivetrain.SetDefaultCommand(Drive(
    &m_drivetrain,
    [this] { return (MathFunctions::joystickCurve(m_controllerMain.GetX(), controllerConstants::kControllerCurve)); },
    [this] { return (MathFunctions::joystickCurve(m_controllerMain.GetY(), controllerConstants::kControllerCurve)); },
    [this] { return (-m_controllerMain.GetRawAxis(4)); }));

    frc2::WaitCommand DoNothing(0_s);
    ScoreHighPreload ScorePreloadHigh(&m_robotArm);
    ScoreMidPreload ScorePreloadMid(&m_robotArm);
    m_startBehaviorChooser.SetDefaultOption("DoNothing", "DoNothing");
    m_startBehaviorChooser.AddOption("ScoreHighPreload", "ScoreHighPreload");
    m_startBehaviorChooser.AddOption("ScoreMidPreload", "ScoreMidPreload");

    m_chooser.SetDefaultOption("DoNothing", "DoNothing");
    m_chooser.AddOption("LeaveCommunity", "LeaveCommunity");
    m_chooser.AddOption("AutoBalance", "AutoBalance");
    m_chooser.AddOption("LeaveCommunityAutoBalance", "LeaveCommunityAutoBalance");
    m_chooser.AddOption("2LowCubeNoBumpSide", "2LowCubeNoBumpSide");
    m_chooser.AddOption("1mTurnTo90", "1mTurnTo90");


    frc::SmartDashboard::PutData(&m_startBehaviorChooser);
    frc::SmartDashboard::PutData(&m_chooser);
    
}

// All the button commands are set in this function
void RobotContainer::ConfigureButtonBindings() {
  //** For commented command file, look at:
  //** ArmUp.cpp and
  //** ArmUp.h

  //Bind Limelight Pipeline 0 (Apriltags) and Pipeline 1 (Retroreflective) to ButtonA and ButtonB events respectively
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kA).WhileTrue(frc2::InstantCommand([this] { m_vision.SelectPipeline(0); }).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kB).WhileTrue(frc2::InstantCommand([this] { m_vision.SelectPipeline(1); }).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kY).WhileTrue(PointAtTarget(&m_drivetrain, &m_vision).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kX).WhileTrue(Align(&m_drivetrain, &m_vision).ToPtr());

  // Zeroing for swervedrive command
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kStart).OnTrue(ZeroGyro(&m_drivetrain).ToPtr());

  // Slow button for swerve (whenever left OR right bumper is held down), slows swerve to slow value
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kRightBumper).OnTrue(SlowDown(&m_drivetrain).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kRightBumper).OnFalse(NormalSpeed(&m_drivetrain).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kLeftBumper).OnTrue(SlowDown(&m_drivetrain).ToPtr());
  frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kLeftBumper).OnFalse(NormalSpeed(&m_drivetrain).ToPtr());

  // Robot arm commands
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kRightBumper).OnTrue(ClampToggle(&m_robotArm).ToPtr());
  
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kY).OnTrue(ScoreHigh(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kX).OnTrue(ScoreMid(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kA).OnTrue(ScoreLow(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kB).OnTrue(GrabCode(&m_robotArm).ToPtr());

  // Zeroing commands and retract arm commands
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kStart).OnTrue(ZeroAngle(&m_robotArm).ToPtr());
  frc2::JoystickButton(&m_controllerOperator, frc::XboxController::Button::kLeftBumper).OnTrue(ArmUp(&m_robotArm).ToPtr());

  // Auto Balance command for driver controller (back button, right next to start button)
  // frc2::JoystickButton(&m_controllerMain, frc::XboxController::Button::kBack).OnTrue(AutoBalance(&m_drivetrain).ToPtr());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  /* if (m_chooser.GetSelected() == "DoNothing")
  {
    return frc2::cmd::Wait(15_s);
  }
  else if (m_chooser.GetSelected() == "ScoreMidPreload")
  {
    return ScoreMidPreload(&m_robotArm).ToPtr();
  }
  else if (m_chooser.GetSelected() == "ScoreHighPreload")
  {
    return ScoreHighPreload(&m_robotArm).ToPtr();
  }
  else
  { */
    std::vector<pathplanner::PathPlannerTrajectory> pathGroup = pathplanner::PathPlanner::loadPathGroup(m_chooser.GetSelected(), {pathplanner::PathConstraints(3_mps, 2_mps_sq)});
    frc2::CommandPtr fullAuto = m_autoBuilder.fullAuto(pathGroup);
    fullAuto.get()->AddRequirements(&m_drivetrain);
    frc2::CommandPtr startBehavior = frc2::cmd::Wait(0_s);
    startBehavior = ((m_startBehaviorChooser.GetSelected() == "ScoreHighPreload") ? ScoreHighPreload(&m_robotArm).ToPtr()
    : ((m_startBehaviorChooser.GetSelected() == "ScoreMidPreload") ? ScoreMidPreload(&m_robotArm).ToPtr()
    : startBehavior));
    return std::move(startBehavior).AndThen(std::move(fullAuto));
  //}
  
  /* if (path == "AutonTest")
  {
    return new Drive(&m_drivetrain, 1_mps, 1_mps, 15_deg_per_s);
  } 
  return &m_Auto;*/
}
