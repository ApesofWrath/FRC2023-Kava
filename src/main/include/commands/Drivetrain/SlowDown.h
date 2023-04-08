#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/drivetrain.h"
#include "Constants.h"

class SlowDown : public frc2::CommandHelper<frc2::CommandBase, SlowDown> {
    public:
    explicit SlowDown(drivetrain* drivetrain);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    drivetrain* m_drivetrain;
};