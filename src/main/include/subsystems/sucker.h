#pragma once

#ifndef SUCKER_H
#define SUCKER_H

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>

#include "Constants.h"

// #include <spanstream>


class Sucker : public frc2::SubsystemBase {
 public:
  Sucker();


 private:
    rev::CANSparkMax m_Elevation1;
    rev::CANSparkMax m_Elevation2;
    rev::CANSparkMax m_Spin1;
    rev::CANSparkMax m_Spin2;

};
#endif // SUCKER_H