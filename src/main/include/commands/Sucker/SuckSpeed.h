#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/sucker.h"

class SuckSpeed : public frc2::CommandHelper<frc2::CommandBase, SuckSpeed> {
    public:
    explicit SuckSpeed(Sucker* Sucker, float speed);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    Sucker* m_sucker;
    float m_speed;
};