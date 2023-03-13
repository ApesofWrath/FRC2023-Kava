#pragma once

#include <ctre/phoenix/sensors/WPI_CANCoder.h>
#include <numbers>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <rev/REVLibError.h>

#include "Constants.h"
#include <string>

enum class AngleStates {
    INIT,
    NOTZEROED,
    ZEROED,
    MANUALZERO,
    IDLE
};

enum class TeleStates {
    INIT,
    NOTZEROED,
    ZEROED,
    MANUALZERO,
    IDLE
};

enum class ScoreHighStates {
    INIT,
    NOTHING,
    FIRSTEXTEND,
    SECONDEXTEND
};

enum class ScoreMidStates {
    INIT,
    NOTHING,
    FIRSTEXTEND,
    SECONDEXTEND
};

enum class ConePickupStates {
    INIT,
    NOTHING,
    FIRSTEXTEND,
    SECONDEXTEND
};

class robotArm : public frc2::SubsystemBase {
    public:
    robotArm();

    void armUp();
    void clampToggle();
    
    void scoreLow();
    void scoreMid();
    void scoreHigh();
    void angleManualZero();
    void grabCone();

    void Periodic() override;

    private:
    rev::CANSparkMax m_motorAngleRight;
    rev::CANSparkMax m_motorAngleLeft;
    rev::CANSparkMax m_motorTelescoping;
    rev::CANSparkMax m_motorClamp;
 
    // ctre::phoenix::sensors::WPI_CANCoder m_encoderTelescoping;
    
    rev::SparkMaxRelativeEncoder m_encoderMotorAngleRight = m_motorAngleRight.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);
    rev::SparkMaxRelativeEncoder m_encoderMotorAngleLeft = m_motorAngleLeft.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);
    rev::SparkMaxRelativeEncoder m_encoderMotorTelescoping = m_motorTelescoping.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);
    rev::SparkMaxRelativeEncoder m_encoderMotorClamp = m_motorClamp.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);

    rev::SparkMaxPIDController m_motorAngleRightController = m_motorAngleRight.GetPIDController();
    rev::SparkMaxPIDController m_motorAngleLeftController = m_motorAngleLeft.GetPIDController();
    rev::SparkMaxPIDController m_motorTelescopingController = m_motorTelescoping.GetPIDController();

    const double m_encoderOffset;

    AngleStates currentStateAngle = AngleStates::INIT;
    TeleStates currentStateTele = TeleStates::INIT;
    ScoreHighStates currentStateHigh = ScoreHighStates::INIT;
    ScoreMidStates currentStateMid = ScoreMidStates::INIT;
    ConePickupStates currentStatePickup = ConePickupStates::INIT;

    bool clawToggle = false;
};