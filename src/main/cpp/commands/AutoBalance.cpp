#include "commands/AutoBalance.h"

#include <frc/MathUtil.h>

AutoBalance::AutoBalance(drivetrain* drivetrain)
    : m_drivetrain{drivetrain}
{
  SetName("AutoBalance");
  AddRequirements({m_drivetrain});
}

void AutoBalance::Initialize() { printf("AutoBalance initialized.\n"); }

void AutoBalance::Execute() {
  if (m_drivetrain->AutoBalance() == "Forward")
  {
    m_drivetrain->SwerveDrive(0.1_mps, 0.0_mps, 0.0_rad_per_s, true);
  }
  if (m_drivetrain->AutoBalance() == "Backward")
  {
    m_drivetrain->SwerveDrive(-0.1_mps, 0.0_mps, 0.0_rad_per_s, true);
  }
  else
  {
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, 0.0_rad_per_s, true);
  }
}
void AutoBalance::End(bool interrupted) { 
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, 0.0_rad_per_s, true); 
}

bool AutoBalance::IsFinished() {
    return m_drivetrain->AutoBalance() == "Stop";
}