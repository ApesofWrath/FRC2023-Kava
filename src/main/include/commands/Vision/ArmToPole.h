#include "frc2/command/CommandBase.h"
#include <frc2/command/CommandHelper.h>
#include <units/velocity.h>
#include <units/angular_velocity.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "subsystems/robotArm.h"
#include "subsystems/vision.h"
#include "Constants.h"
class ArmToPole : public frc2::CommandHelper<frc2::CommandBase, ArmToPole> {
public:
  explicit ArmToPole(robotArm* m_robotArm, Vision* Vision);
    // Use Requires() here to declare subsystem dependencies
    // eg. Requires(&Robot::m_subsystem);

  void Initialize() override;
    // Perform any initialization steps for this command
  

  void Execute() override;
    // Code that is run repeatedly while the command is scheduled
  

  bool IsFinished() override;
    // Return true when the command should end, typically based on sensor readings or user input


  void End(bool interrupted) override;
    // Perform any clean-up steps when the command ends
  private:
    robotArm* m_robotArm;
    Vision* m_vision;
  };