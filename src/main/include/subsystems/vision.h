#pragma once

#ifndef VISION_H
#define VISION_H

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <frc/geometry/Pose2d.h>
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableValue.h"
#include "wpi/SpanExtras.h"
#include <span>

// #include <spanstream>

enum class PoleHeight {HIGH, LOW};
enum class PoleColumn {LEFT, RIGHT};
class Vision : public frc2::SubsystemBase {
 public:
  Vision();

  PoleHeight targetPoleHeight;
  PoleColumn targetPoleColumn;
  double GetTargetX();
  void SelectPipeline(int id);
  std::vector<double> GetBotPose();
  std::vector<double> GetTargetPoseRobotSpace();
  std::vector<double> GetRobotPoseTargetSpace();
  double GetPoleDistance();
  frc::Pose2d ToPose2d();
  bool TargetFound();
  double GetLatency();

 private:
  std::vector<double> getNearestPole();
  std::shared_ptr<nt::NetworkTable> m_networkTable;
  // std::vector<std::vector<double>> polePositions{
  //   //Pole Positions Left to right, with the top pole first (from POV of the center of the field)
  //   //Red
  //   {7.884, 0.973, 1.17},
  //   {7.869, 0.981, 0.734},

  //   {7.884, -0.143, 1.17},
  //   {7.869, -0.143, 0.734},
    
  //   {7.884, -0.7, 1.17},
  //   {7.869, -0.7, 0.734},
    
  //   {7.884, -1.815, 1.17},
  //   {7.869, -1.815, 0.734},

  //   {7.884, -2.377, 1.17},
  //   {7.869, -2.377, 0.734},

  //   {7.884, -3.495, 1.17},
  //   {7.869, -3.495, 0.734},
  // };
  // Eigen::Matrix polePositions(12, 3);

};
#endif // VISION_H