#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/sensors/WPI_CANCoder.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <units/angular_velocity.h>
#include <units/time.h>
#include <units/velocity.h>
#include <numbers>
#include <rev/SparkMaxRelativeEncoder.h>
#include <rev/CANSparkMax.h>
#include <frc/kinematics/SwerveModulePosition.h>

#include "Constants.h"
#include "hardwareSettings.h"

class robotArm {
    public:
    robotArm(const double arm[]);

    void armDown();
    void armUp();

    private:
    rev::CANSparkMax m_motorAngleRight;
    rev::CANSparkMax m_motorAngleLeft;
    rev::CANSparkMax m_motorTelescoping;
    rev::CANSparkMax m_motorClamp;

    ctre::phoenix::sensors::WPI_CANCoder m_encoderTelescoping;
    
    rev::SparkMaxRelativeEncoder m_encoderMotorAngleRight = m_motorAngleRight.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);
    rev::SparkMaxRelativeEncoder m_encoderMotorAngleLeft = m_motorAngleLeft.GetEncoder(rev::SparkMaxRelativeEncoder::Type::kHallSensor, 42);

    rev::SparkMaxPIDController m_motorAngleRightController = m_motorAngleRight.GetPIDController();
    rev::SparkMaxPIDController m_motorAngleLeftController = m_motorAngleLeft.GetPIDController();

    const double m_encoderOffset;
};