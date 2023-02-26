#pragma once

#include <ctre/phoenix/sensors/WPI_CANCoder.h>
#include <numbers>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>

#include <rev/REVLibError.h>

#include "Constants.h"
#include "hardwareSettings.h"
#include <string>

class robotArm : public frc2::SubsystemBase {
    public:
    robotArm();

    void armDown();
    void armUp();
    void teleOut();
    void teleIn();
    void clampClose();
    void clampOpen();

    void Periodic() override;

    private:
    rev::CANSparkMax m_motorAngleRight;
    rev::CANSparkMax m_motorAngleLeft;
    rev::CANSparkMax m_motorTelescoping;
    rev::CANSparkMax m_motorClamp;
 
    ctre::phoenix::sensors::WPI_CANCoder m_encoderTelescoping;
    
    rev::SparkMaxRelativeEncoder m_encoderMotorAngleRight = m_motorAngleRight.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);
    rev::SparkMaxRelativeEncoder m_encoderMotorAngleLeft = m_motorAngleLeft.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);
    rev::SparkMaxRelativeEncoder m_encoderMotorTelescoping = m_motorTelescoping.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);

    rev::SparkMaxPIDController m_motorAngleRightController = m_motorAngleRight.GetPIDController();
    rev::SparkMaxPIDController m_motorAngleLeftController = m_motorAngleLeft.GetPIDController();
    rev::SparkMaxPIDController m_motorTelescopingController = m_motorTelescoping.GetPIDController();

    const double m_encoderOffset;
};