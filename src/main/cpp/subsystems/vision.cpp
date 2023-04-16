#include "subsystems/vision.h"
//Class for Vision
Vision::Vision()
    : m_networkTable(nt::NetworkTableInstance::GetDefault().GetTable("limelight")) {}

//Get X coordinate of target
double Vision::GetTargetX() {
  return m_networkTable->GetNumber("tx", 0.0);
}

//Set pipeline of limelight given id
void Vision::SelectPipeline(int id){
  m_networkTable->PutNumber("pipeline", id);
}
//Get Robot's Pose
std::vector<double> Vision::GetBotPose() {
  double defaultbotpose[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  return m_networkTable->GetNumberArray("botpose", std::span<double>(defaultbotpose, 6));
}

std::vector<double> Vision::GetTargetPoseRobotSpace() {
  double defaultbotpose[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  return m_networkTable->GetNumberArray("targetpose_robotspace", std::span<double>(defaultbotpose, 6));
}

double Vision::GetPoleDistance(){
  std::vector<double> targetPose = this->GetTargetPoseRobotSpace();
  double tx = targetPose[0];
  double tz = targetPose[2];
  double distance = tz + sqrt(0.347+tx);
  frc::SmartDashboard::PutNumber("Distance to pole", distance);
  return distance;
}

frc::Pose2d Vision::ToPose2d() {
  std::vector<double> defaultbotpose;
  if (m_networkTable->GetNumber("tv", 0) != 1.0) {
    return frc::Pose2d(0_m, 0_m, 0_deg);
  }

  if (frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kBlue) {
      defaultbotpose = m_networkTable->GetNumberArray("botpose_wpiblue", std::span<const double>());
  } 
  else {
      defaultbotpose = m_networkTable->GetNumberArray("botpose_wpired", std::span<const double>());
  }

  if (defaultbotpose.size() < 6) {
      return frc::Pose2d(0_m, 0_m, 0_deg);
  }
        
  
  return frc::Pose2d(frc::Translation2d(units::meter_t (defaultbotpose[0]), units::meter_t (defaultbotpose[1])), frc::Rotation2d(units::degree_t (defaultbotpose[5])));
}

bool Vision::TargetFound() {
  return m_networkTable->GetNumber("tv", 0) == 1.0;
}
double Vision::GetLatency() {
  double defaultbotpose[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  std::vector<double> botpose = m_networkTable->GetNumberArray("botpose", std::span<double>(defaultbotpose, 7));
  return botpose[6];
}