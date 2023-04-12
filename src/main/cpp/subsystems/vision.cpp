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