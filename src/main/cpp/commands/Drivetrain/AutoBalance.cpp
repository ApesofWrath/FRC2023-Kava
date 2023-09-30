#include "commands/Drivetrain/AutoBalance.h"

#include <frc/MathUtil.h>

AutoBalance::AutoBalance(drivetrain* drivetrain)
    : m_drivetrain{drivetrain}, m_timer{}, m_balancedTimer{}
{
  SetName("AutoBalance");
  AddRequirements({m_drivetrain});
}

void AutoBalance::Initialize() 
{
   printf("AutoBalance initialized.\n"); 
   m_timer.Stop();
   m_timer.Reset();
   m_timer.Start();
}

void AutoBalance::Execute() {
  frc::SmartDashboard::PutString("Auto Bal", m_drivetrain->AutoBalance());
  m_drivetrain->SwerveDrive(((m_drivetrain->AutoBalance() == "Forward") ? 0.28_mps : 
  ((m_drivetrain->AutoBalance() == "ForwardSlow") ? 0.2_mps : 
  ((m_drivetrain->AutoBalance() == "Backward") ? -0.28_mps : 
  ((m_drivetrain->AutoBalance() == "BackwardSlow") ? -0.2_mps : 0.0_mps)))), 0.0_mps, 0.0_rad_per_s, true);

  if (m_drivetrain->AutoBalance() != "Forward" && m_drivetrain->AutoBalance() != "ForwardSlow" && m_drivetrain->AutoBalance() != "Backward" && m_drivetrain->AutoBalance() != "BackwardSlow") {
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, 0.0_rad_per_s, true);
    printf("Stop (Balanced) \n");
    m_balancedTimer.Start();
  }
  else
  {
    m_balancedTimer.Stop();
    m_balancedTimer.Reset();
  }
}

void AutoBalance::End(bool interrupted) { 
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, 0.0_rad_per_s, true); 
    m_balancedTimer.Stop();
    m_timer.Stop();
}

bool AutoBalance::IsFinished() {
    return (m_drivetrain->AutoBalance() == "Stop" && m_balancedTimer.Get() > 3.5_s) || m_timer.Get() > 5_s;
}