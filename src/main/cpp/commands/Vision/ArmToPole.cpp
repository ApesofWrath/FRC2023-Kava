#include "commands/Vision/ArmToPole.h"
#include "MathFunctions.h"

ArmToPole::ArmToPole(robotArm* robotArm, Vision* vision) : m_robotArm(robotArm), m_vision(vision) {
    printf("ArmToPole initialized! \n"); 
    SetName("ArmToPole");
    AddRequirements({robotArm});
}

void ArmToPole::Initialize() { printf("ArmToPole Initialized \n"); }

void ArmToPole::Execute() {

    double poleDistance = m_vision->GetPoleDistance();
    double pivotOffset = 0.3;
    double poleHeight = 1.0;
    double collapsedArmLength = 1.0;
    double armExtend = sqrt(pow(poleDistance+pivotOffset, 2)+pow(poleHeight, 2))-collapsedArmLength;
    double armAngle = atan(poleHeight/(pivotOffset+poleDistance));
           
}

void ArmToPole::End(bool interrupted) {interrupted ? printf("ArmToPole Inturrupted! \n") : printf("ArmToPole Finished!");}

bool ArmToPole::IsFinished() { return false; }