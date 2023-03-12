#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/robotArm.h"

class GrabCode : public frc2::CommandHelper<frc2::CommandBase, GrabCode> {
    public:
    explicit GrabCode(robotArm* robotArm);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    robotArm* m_robotArm;
};