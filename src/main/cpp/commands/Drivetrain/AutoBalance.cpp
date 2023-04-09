#include "commands/Drivetrain/AutoBalance.h"

#include <frc/MathUtil.h>

AutoBalance::AutoBalance(drivetrain* drivetrain)
    : m_drivetrain{drivetrain}, m_timer{}
{
  SetName("AutoBalance");
  AddRequirements({m_drivetrain});
}

void AutoBalance::Initialize() { printf("AutoBalance initialized.\n"); }

void AutoBalance::Execute() {
  m_drivetrain->SwerveDrive(((m_drivetrain->AutoBalance() == "Forward") ? 0.3_mps : ((m_drivetrain->AutoBalance() == "ForwardSlow") ? 0.15_mps : ((m_drivetrain->AutoBalance() == "Backward") ? -0.3_mps : ((m_drivetrain->AutoBalance() == "BackwardSlow") ? -0.15_mps : 0.0_mps)))), 0.0_mps, 0.0_rad_per_s, true);

  if (m_drivetrain->AutoBalance() != "Forward" && m_drivetrain->AutoBalance() != "ForwardSlow" && m_drivetrain->AutoBalance() != "Backward" && m_drivetrain->AutoBalance() != "BackwardSlow") {
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, 0.0_rad_per_s, true);
    printf("stop \n");
    m_timer.Reset();
    m_timer.Start();
  }
}

void AutoBalance::End(bool interrupted) { 
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, 0.0_rad_per_s, true); 
    m_timer.Stop();
}

bool AutoBalance::IsFinished() {
    return m_drivetrain->AutoBalance() == "Stop" && m_timer.Get() > 1_s;
}