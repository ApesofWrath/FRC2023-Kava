#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/robotArm.h"

class ArmUp : public frc2::CommandHelper<frc2::CommandBase, ArmUp> {
    public:
    explicit ArmUp(robotArm* robotArm);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    // Creates robotArm pointer to robotArm subsystem
    robotArm* m_robotArm;
};