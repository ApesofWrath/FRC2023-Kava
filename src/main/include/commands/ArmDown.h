#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "robotArm.h"

class ArmDown : public frc2::CommandHelper<frc2::CommandBase, ArmDown> {
    public:
    explicit ArmDown(robotArm* subsystem);

    void Initialize() override;

    bool IsFinished() override;

    private:
    robotArm* m_arm;
};