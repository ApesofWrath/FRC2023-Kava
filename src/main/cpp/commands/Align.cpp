#include "commands/Align.h"


Align::Align(drivetrain* drivetrain, Vision* vision) : m_drivetrain(drivetrain), m_vision(vision) {
    printf("Align initialized! \n");
    SetName("Align");
    AddRequirements({m_drivetrain});
}


void Align::Initialize() { printf("Aligning Initialized \n"); }


void Align::Execute() {
    // Calculate Error
    std::vector<double> TargetPose =  m_vision->GetTargetPoseRobotSpace();
    double xerror = TargetPose[0]*visionConstants::xAlignMultiplier;
    double Targetx = m_vision->GetTargetX();
    double yawerror = Targetx*visionConstants::errorMultiplier;
    double yerror = (std::abs(TargetPose[2]-visionConstants::AlignDistance))*visionConstants::zAlignMultiplier;
    // double yawerror;
    // if (TargetPose[2]<= visionConstants::rotationDistance){
    //     double yawerror = TargetPose[5]*visionConstants::yawAlignMultiplier;
    // }else{
    //     double yawerror = 0;
    // }
    
    // Convert all values to respective unit types
    units::meters_per_second_t xerror_m{xerror};
    units::meters_per_second_t yerror_m{yerror};
    units::radians_per_second_t yawerrorrps{yawerror};
    // units::radians_per_second_t error_rps{error};
    // frc::SmartDashboard::PutNumber("Tx Error", error);
    // Move robot
    m_drivetrain->SwerveDrive(xerror_m, yerror_m, yawerrorrps, false);
       
}


void Align::End(bool interrupted) {interrupted ? printf("Alligned Inturrupted!") : printf("Align Finished!");}


bool Align::IsFinished() { return false; }