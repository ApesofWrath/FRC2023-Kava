#include "subsystems/vision.h"

Vision::Vision()
    : m_networkTable(nt::NetworkTableInstance::GetDefault().GetTable("limelight")) {}

double Vision::GetTargetX() {
  return m_networkTable->GetNumber("tx", 0.0);
}
