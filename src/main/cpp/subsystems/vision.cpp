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
};