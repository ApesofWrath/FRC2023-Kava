#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/drivetrain.h"
#include "Constants.h"

class NormalSpeed : public frc2::CommandHelper<frc2::CommandBase, NormalSpeed> {
    public:
    explicit NormalSpeed(drivetrain* drivetrain);

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    private:
    drivetrain* m_drivetrain;
};