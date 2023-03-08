#include "commands/Align.h"

Align::Align(drivetrain* drivetrain, Vision* vision) : m_drivetrain(drivetrain), m_vision(vision) {
    printf("Align initialized! \n"); 
    SetName("Align");
    AddRequirements({m_drivetrain});
}

void Align::Initialize() { printf("Aligning Initialized \n"); }

void Align::Execute() {
    // Calculate Error
    double error =  m_vision->GetTargetX()*visionConstants::errorMultiplier;
    // If error is greater than or equal to minumum error
    // if (error >= visionConstants::errorMinimum){
    units::radians_per_second_t error_rps{error};
    frc::SmartDashboard::PutNumber("Tx Error", error);
    // Move robot
    m_drivetrain->SwerveDrive(0.0_mps, 0.0_mps, error_rps, false);
    // }
       
}

void Align::End(bool interrupted) {interrupted ? printf("Alligned Inturrupted!") : printf("Align Finished!");}

bool Align::IsFinished() { return false; }