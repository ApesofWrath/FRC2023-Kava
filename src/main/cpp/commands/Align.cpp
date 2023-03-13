#include "commands/Align.h"


Align::Align(drivetrain* drivetrain, Vision* vision) : m_drivetrain(drivetrain), m_vision(vision) {
    printf("Align initialized! \n");
    SetName("Align");
    AddRequirements({m_drivetrain});
}


void Align::Initialize() { printf("Aligning Initialized \n"); }


void Align::Execute() {
    // Get Target information from Limelight
    std::vector<double> TargetPose =  m_vision->GetTargetPoseRobotSpace();
    double Targetx = m_vision->GetTargetX();
    // Calculate errors
    std::vector<double> TargetPosition{TargetPose[0], TargetPose[1]};
    std::vector<double> TargetNormal{TargetPose[3], TargetPose[4]};
    // std::vector<double> DestinationPosition{TargetPose[0]+(TargetNormal[0]*visionConstants::AlignDistance), TargetPose[1]+(TargetNormal[1]*visionConstants::AlignDistance)}; 
    double xerror = TargetPosition[0]*visionConstants::xAlignMultiplier;
    double yerror = TargetPosition[1]*visionConstants::zAlignMultiplier;    
    double yawerror = Targetx*visionConstants::errorMultiplier;

    // std::span<double> TargetPositionSpan = std::span<double>(TargetPosition.data(), TargetPosition.size());
    // std::span<double> TargetNormalSpan = std::span<double>(TargetNormal.data(), TargetNormal.size());
    // std::span<double> DestinationPositionSpan = std::span<double>(DestinationPosition.data(), DestinationPosition.size());
    // frc::SmartDashboard::PutNumber("xerror", xerror);
    // frc::SmartDashboard::PutNumber("yerror", yerror);
    // frc::SmartDashboard::PutNumber("yawerror", yawerror);
    // frc::SmartDashboard::PutNumber("Targetx", Targetx);
    // Convert all values to respective unit types
    units::meters_per_second_t xerror_m{xerror};
    units::meters_per_second_t yerror_m{yerror};
    units::radians_per_second_t yawerrorrps{yawerror};

    // Move robot
    m_drivetrain->SwerveDrive(xerror_m, yerror_m, yawerrorrps, false);
       
}


void Align::End(bool interrupted) {interrupted ? printf("Alligned Inturrupted!") : printf("Align Finished!");}


bool Align::IsFinished() { return false; }