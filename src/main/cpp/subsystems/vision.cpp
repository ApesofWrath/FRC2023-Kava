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

std::vector<double> Vision::GetRobotPoseTargetSpace() {
  double defaultbotpose[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  return m_networkTable->GetNumberArray("botpose_targetspace", std::span<double>(defaultbotpose, 6));
}

double Vision::GetPoleDistance(){

  std::vector<double> robotPose = this->GetRobotPoseTargetSpace();
  double px;
  double pz;
  switch (targetPoleHeight)
  {
  case PoleHeight::LOW:
    px = -0.2;
    break;
  case PoleHeight::HIGH:
    px = -0.65;
      break;
  default:
    break;
  }

  switch (targetPoleColumn)
  {
    case PoleColumn::LEFT:
      px = -0.572;
      break;

    case PoleColumn::RIGHT:
      px = 0.572;
      break;

    default:

      break;
  }
  double rx = robotPose[0];
  double rz = robotPose[2];
  frc::SmartDashboard::PutNumber("rx", rx);
  frc::SmartDashboard::PutNumber("rz", rz);

  px = -0.572;
  pz = 0.2;
  double distance = sqrt(pow(rx-px, 2)+pow(rz-pz, 2));
  frc::SmartDashboard::PutNumber("Distance to pole", distance);
  return distance;
}

// std::vector<double> Vision::getNearestPole(){
//   std::vector<double> botpose = GetBotPose();
  


// }