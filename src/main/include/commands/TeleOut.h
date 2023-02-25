#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/robotArm.h"

class TeleOut : public frc2::CommandHelper<frc2::CommandBase, TeleOut> {
    public:
    explicit TeleOut(robotArm* robotArm);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    robotArm* m_robotArm;
};