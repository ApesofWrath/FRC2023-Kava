#pragma once
#include "subsystems/robotArm.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/MathUtil.h>
#include <iostream>
#include <numbers>
#include <frc/geometry/Rotation2d.h>

robotArm::robotArm()
: m_motorAngleLeft(armConstants::arm::kRobotArm[0], rev::CANSparkMax::MotorType::kBrushless),
m_motorAngleRight(armConstants::arm::kRobotArm[1], rev::CANSparkMax::MotorType::kBrushless),
/* m_motorTelescoping(armConstants::arm::kRobotArm[2], rev::CANSparkMax::CANSparkMax::MotorType::kBrushless),
m_motorClamp(armConstants::arm::kRobotArm[3], rev::CANSparkMax::CANSparkMax::MotorType::kBrushless),
 */m_encoderTelescoping(armConstants::arm::kRobotArm[4]),
m_encoderOffset(armConstants::arm::kRobotArm[5]) {

    m_encoderTelescoping.ConfigMagnetOffset(m_encoderOffset);
    m_encoderTelescoping.ConfigSensorDirection(true);

    m_motorAngleLeft.RestoreFactoryDefaults();
    m_motorAngleRight.RestoreFactoryDefaults();
    /* m_motorTelescoping.RestoreFactoryDefaults();
    m_motorClamp.RestoreFactoryDefaults();
 */
    m_motorAngleLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_motorAngleRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_motorAngleLeftController.SetFeedbackDevice(m_encoderMotorAngleLeft);

    m_motorAngleLeftController.SetP(0);
    m_motorAngleLeftController.SetI(0);
    m_motorAngleLeftController.SetD(0);
    m_motorAngleLeftController.SetFF(1.0/5767.0);
    m_motorAngleLeftController.SetOutputRange(-1.0F, 1.0F);

    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 4.0);
    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, -38.0);

    m_motorAngleLeftController.SetSmartMotionMaxVelocity(7200);
    m_motorAngleLeftController.SetSmartMotionMaxAccel(28800);
    m_motorAngleLeftController.SetSmartMotionMinOutputVelocity(0);
    m_motorAngleLeftController.SetSmartMotionAllowedClosedLoopError(0);

    m_motorAngleRight.Follow(m_motorAngleLeft, true);
}

void robotArm::armDown() {
    m_motorAngleLeftController.SetReference(-20, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::armUp() {
    m_motorAngleLeftController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::teleOut() { }

void robotArm::teleIn() { }

void robotArm::Periodic() { }