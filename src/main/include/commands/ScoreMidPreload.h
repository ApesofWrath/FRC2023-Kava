#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/robotArm.h"

class ScoreMidPreload : public frc2::CommandHelper<frc2::SequentialCommandGroup, ScoreMidPreload> {
    public:
    explicit ScoreMidPreload(robotArm* robotArm);

   // void Initialize() override;

   // void Execute() override;

   // bool IsFinished() override;

    private:
    robotArm* m_robotArm;
};