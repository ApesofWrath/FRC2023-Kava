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
m_motorTelescoping(armConstants::arm::kRobotArm[2], rev::CANSparkMax::MotorType::kBrushless),
m_motorClamp(armConstants::arm::kRobotArm[3], rev::CANSparkMax::MotorType::kBrushless),
m_encoderTelescoping(armConstants::arm::kRobotArm[4]),
m_encoderOffset(armConstants::arm::kRobotArm[5]) {

    m_encoderTelescoping.ConfigMagnetOffset(m_encoderOffset);
    m_encoderTelescoping.ConfigSensorDirection(true);

    m_motorAngleLeft.RestoreFactoryDefaults();
    m_motorAngleRight.RestoreFactoryDefaults();
    m_motorTelescoping.RestoreFactoryDefaults();
    m_motorClamp.RestoreFactoryDefaults();
 
    m_motorAngleLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_motorAngleRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_motorAngleLeftController.SetFeedbackDevice(m_encoderMotorAngleLeft);
    m_motorTelescopingController.SetFeedbackDevice(m_encoderMotorTelescoping);

    m_motorAngleLeftController.SetP(0.00005);
    m_motorAngleLeftController.SetI(0);
    m_motorAngleLeftController.SetD(0);
    m_motorAngleLeftController.SetFF(1.0/5767.0);
    m_motorAngleLeftController.SetOutputRange(-1.0F, 1.0F);

    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 4.0);
    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, -38.0);

    m_motorAngleLeftController.SetSmartMotionMaxVelocity(7200);
    m_motorAngleLeftController.SetSmartMotionMaxAccel(24800);
    m_motorAngleLeftController.SetSmartMotionMinOutputVelocity(0);
    m_motorAngleLeftController.SetSmartMotionAllowedClosedLoopError(0);

    m_motorTelescopingController.SetP(0);
    m_motorTelescopingController.SetI(0);
    m_motorTelescopingController.SetD(0);
    m_motorTelescopingController.SetFF(1.0/5767.0);
    m_motorTelescopingController.SetOutputRange(-1.0F, 1.0F);

    m_motorTelescopingController.SetSmartMotionMaxVelocity(2400);
    m_motorTelescopingController.SetSmartMotionMaxAccel(9600);
    m_motorTelescopingController.SetSmartMotionMinOutputVelocity(0);
    m_motorTelescopingController.SetSmartMotionAllowedClosedLoopError(0);

    m_motorClamp.SetSmartCurrentLimit(1.0);
    m_motorClamp.SetInverted(true);
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 5.0);
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 24.0);

    m_motorAngleRight.Follow(m_motorAngleLeft, true);
}

void robotArm::armDown() {
    m_motorAngleLeftController.SetReference(-27, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::armUp() {
    m_motorAngleLeftController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::teleOut() { 
    m_motorTelescopingController.SetReference(157.5, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::teleIn() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);

}

void robotArm::clampClose() {
    m_motorClamp.Set(0.5);
}

void robotArm::clampOpen() {
    m_motorClamp.Set(-0.5);
}

void robotArm::Periodic() {
    frc::SmartDashboard::SmartDashboard::PutNumber("Tel Rel Enc Pos: ", m_encoderMotorTelescoping.GetPosition());
}