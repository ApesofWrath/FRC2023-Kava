#include "commands/Align.h"

Align::Align(drivetrain* drivetrain, Vision* vision) : m_drivetrain(drivetrain), m_vision(vision) {
    printf("Align initialized! \n"); 
    SetName("Align");
    AddRequirements({m_drivetrain});
}

void Align::Initialize() { printf("Aligning Start!! \n"); }

void Align::Execute() {
    printf("Alligning! \n");
    // Calculate Error
    double error =  m_vision->GetTargetX()*visionConstants::errorMultiplier;
    // If error is greater than or equal to minumum error
    if (error >= visionConstants::errorMinimum){
        printf("IF STATEMENT \n");
        units::radians_per_second_t error_rps{error};
        units::meters_per_second_t error_mps{error};
        double error_unrps{error_rps};
        frc::SmartDashboard::PutNumber("Tx Error", error);
        frc::SmartDashboard::PutNumber("Tx Rad Error", error_unrps);
        // Move robot
        m_drivetrain->SwerveDrive(error_mps, 0.0_mps, 0.0_rad_per_s, false);
    }
       
}

void Align::End(bool interrupted) {interrupted ? printf("Alligned Inturrupted!") : printf("Align Finished!");}

bool Align::IsFinished() { return false; }