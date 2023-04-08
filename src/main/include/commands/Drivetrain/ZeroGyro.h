#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/drivetrain.h"

class ZeroGyro : public frc2::CommandHelper<frc2::CommandBase, ZeroGyro> {
    public:
    explicit ZeroGyro(drivetrain* drivetrain);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    drivetrain* m_drivetrain;
};