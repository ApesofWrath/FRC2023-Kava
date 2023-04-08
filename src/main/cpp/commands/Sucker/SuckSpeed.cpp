#include "commands/Sucker/SuckSpeed.h" // relevent header file

SuckSpeed::SuckSpeed(Sucker* Sucker, float speed) : m_sucker{Sucker}, m_speed{speed} { // constructor for command class
    SetName("SuckSpeed"); // set the ?? name
    AddRequirements({m_sucker}); // require the m_drivetrain pointer
}

void SuckSpeed::Initialize() {} // print debug message on initialization

void SuckSpeed::Execute() { // on command call (button press)
    m_sucker->SetSpinSpeed(m_speed);
}

bool SuckSpeed::IsFinished() { return false; } // return when ??