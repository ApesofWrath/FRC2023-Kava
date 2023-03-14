#include "commands/PointAtTarget.h"

PointAtTarget::PointAtTarget(drivetrain* drivetrain, Vision* vision) : m_drivetrain(drivetrain), m_vision(vision) {
    printf("PointAtTarget initialized! \n"); 
    SetName("PointAtTarget");
    AddRequirements({m_drivetrain});
}

void PointAtTarget::Initialize() { printf("PointAtTarget Initialized \n"); }

void PointAtTarget::Execute() {
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

void PointAtTarget::End(bool interrupted) {interrupted ? printf("Alligned Inturrupted! \n") : printf("PointAtTarget Finished!");}

bool PointAtTarget::IsFinished() { return false; }