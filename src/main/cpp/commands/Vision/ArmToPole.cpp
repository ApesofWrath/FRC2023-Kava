#include "commands/Vision/ArmToPole.h"
#include "frc/smartdashboard/SmartDashboard.h"


ArmToPole::ArmToPole(robotArm* robotArm, Vision* vision) : m_robotArm(robotArm), m_vision(vision) {
    printf("ArmToPole initialized! \n"); 
    SetName("ArmToPole");
    AddRequirements({robotArm});
}

void ArmToPole::Initialize() { printf("ArmToPole Initialized \n"); }

void ArmToPole::Execute() {
    double poleDistance = m_vision->GetPoleDistance();
    double pivotOffset = 0.215;
    double poleHeight;
    switch (m_vision->targetPoleHeight){
        case PoleHeight::LOW:
            poleHeight = 0.864;
            break;
        case PoleHeight::HIGH:
            poleHeight = 1.16;
            break;
    }
    // double poleHeight = 0.864;
    double collapsedArmLength = 0.887;
    double armExtend = sqrt(pow(poleDistance+pivotOffset, 2)+pow(poleHeight, 2))-collapsedArmLength;
    double armAngle = ((atan(poleHeight/(pivotOffset+poleDistance))) - (3.141592653589/2))+0.087266;

    double armExtendOg = armExtend;
    double armAngleOg = armAngle;

    // if (armExtend > 1.07) {
    //     armExtend = 1.07;
    // } else if (armExtend < 0) {
    //     armExtend = 0;
    // } else {

    // }
    armExtend = std::clamp(armExtend, 0.0, 1.2);

    // if (armAngle < -1.1) {
    //     armAngle = -1.1;
    // } else if (armAngle > 0) {
    //     armAngle = 0;
    // } else {
        
    // }
    armAngle = std::clamp(armAngle, -1.1, 0.0);

    m_robotArm->setArmPos(armAngle, armExtend);
    frc::SmartDashboard::PutNumber("armExtend", armExtend);
}

void ArmToPole::End(bool interrupted) {interrupted ? printf("ArmToPole Inturrupted! \n") : printf("ArmToPole Finished!");}

bool ArmToPole::IsFinished() { return true; }