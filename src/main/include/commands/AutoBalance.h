#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <frc/filter/SlewRateLimiter.h>
#include <frc/Timer.h>
#include "subsystems/drivetrain.h"

/**
*
*/
class AutoBalance
    : public frc2::CommandHelper<frc2::CommandBase, AutoBalance> {
 public:
  /**
   * Creates a new instance of Drive command.
   *
   */
  explicit AutoBalance(drivetrain* drivetrain);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  drivetrain* m_drivetrain;
  frc::Timer m_timer;
};
