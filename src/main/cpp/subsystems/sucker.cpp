#include "subsystems/sucker.h"
using namespace suckerConstants;
//Class for Sucker
Sucker::Sucker() : m_Elevation1(elevation1Id, rev::CANSparkMax::MotorType::kBrushless),
m_Elevation2(elevation2Id, rev::CANSparkMax::MotorType::kBrushless),
m_Spin1(Spin1Id, rev::CANSparkMax::MotorType::kBrushless),
m_Spin2(Spin2Id, rev::CANSparkMax::MotorType::kBrushless){}
