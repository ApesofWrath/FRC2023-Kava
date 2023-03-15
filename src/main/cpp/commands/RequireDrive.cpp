#include "commands/RequireDrive.h"

#include <frc/MathUtil.h>

RequireDrive::RequireDrive(drivetrain* drivetrain)
    :m_drivetrain{drivetrain}  {
  SetName("RequireDrive");
  AddRequirements({m_drivetrain});
}

void RequireDrive::Initialize() { printf("RequireDrive initialized.\n"); }

void RequireDrive::Execute() {
}

void RequireDrive::End(bool interrupted) { printf("**Drive has been interrupted!**\n"); }

bool RequireDrive::IsFinished() { return false; }