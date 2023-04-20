#include "subsystems/vision.h"
//Class for Vision
Vision::Vision()
    : m_networkTable(nt::NetworkTableInstance::GetDefault().GetTable("limelight")) {}

void Vision::Periodic() {
  switch (targetPoleHeight){
    case PoleHeight::HIGH:
    switch (targetPoleColumn){
      case PoleColumn::LEFT:
        this->SelectPipeline(0);
        break;
      case PoleColumn::RIGHT:
        this->SelectPipeline(1);
        break;

    }
      frc::SmartDashboard::PutString("Target Pole Height", "High");
      break;

    case PoleHeight::LOW:
      frc::SmartDashboard::PutString("Target Pole Height", "Low");
      switch (targetPoleColumn){
        case PoleColumn::LEFT:
          this->SelectPipeline(2);
          break;
        case PoleColumn::RIGHT:
          this->SelectPipeline(3);
          break;
      break;

    default:
      frc::SmartDashboard::PutString("Target Pole Height", "None");
      break;
      }
    
  }

  switch (targetPoleColumn) {
  case PoleColumn::LEFT:
    frc::SmartDashboard::PutString("Target Pole Column", "Left");
    break;

  case PoleColumn::RIGHT:
    frc::SmartDashboard::PutString("Target Pole Column", "Right");
    break;

  default:
    frc::SmartDashboard::PutString("Target Pole Column", "None");
    break;

  }
  

  if (this->GetTargetPoseRobotSpace()[0] > 0.0) {
    targetPoleColumn = PoleColumn::LEFT;
  } else {
    targetPoleColumn = PoleColumn::RIGHT;
  }
}
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

void Vision::setPole(PoleHeight height){
  targetPoleHeight = height;
}

void Vision::setPole(PoleColumn column){
  targetPoleColumn = column;
}

void Vision::setPole(PoleHeight height, PoleColumn column){
  targetPoleHeight = height;
  targetPoleColumn = column;
}

double Vision::GetPoleDistance(){

  std::vector<double> robotPose = this->GetRobotPoseTargetSpace();
  double px;
  double pz;
  switch (targetPoleHeight)
  {
  case PoleHeight::LOW:
    pz = -0.2;
    break;
  case PoleHeight::HIGH:
    pz = -0.65;
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

  // px = -0.572;
  // pz = 0.2;
  double distance = sqrt(pow(rx-px, 2)+pow(rz-pz, 2));
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