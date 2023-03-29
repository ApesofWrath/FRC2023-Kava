#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/filter/SlewRateLimiter.h>

#include "subsystems/drivetrain.h"

/**
*
*/
class RequireDrive
    : public frc2::CommandHelper<frc2::CommandBase, RequireDrive> {
 public:
  
  explicit RequireDrive(drivetrain* drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  drivetrain* m_drivetrain;
};
