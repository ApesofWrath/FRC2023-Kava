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

    m_motorAngleLeftController.SetSmartMotionMaxVelocity(5600); //7200
    m_motorAngleLeftController.SetSmartMotionMaxAccel(10800); //24800
    m_motorAngleLeftController.SetSmartMotionMinOutputVelocity(0); //0
    m_motorAngleLeftController.SetSmartMotionAllowedClosedLoopError(0); //0

    m_motorTelescopingController.SetP(0);
    m_motorTelescopingController.SetI(0);
    m_motorTelescopingController.SetD(0);
    m_motorTelescopingController.SetFF(1.0/5767.0);
    m_motorTelescopingController.SetOutputRange(-1.0F, 1.0F);

    m_motorTelescopingController.SetSmartMotionMaxVelocity(8400); //2400
    m_motorTelescopingController.SetSmartMotionMaxAccel(17200); //9600
    m_motorTelescopingController.SetSmartMotionMinOutputVelocity(0); //0
    m_motorTelescopingController.SetSmartMotionAllowedClosedLoopError(0); //0

    m_motorClamp.SetSmartCurrentLimit(1.0);
    m_motorClamp.SetInverted(true);
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 5.0);
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 38.0);

    m_motorClamp.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    m_motorClamp.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);

    m_motorAngleLeft.SetSmartCurrentLimit(40.0);
    m_motorAngleRight.SetSmartCurrentLimit(40.0);
    m_motorTelescoping.SetSmartCurrentLimit(40.0);

    m_motorTelescoping.SetInverted(true);

    m_motorAngleRight.Follow(m_motorAngleLeft, true);
}

void robotArm::armDown() {
    m_motorAngleLeftController.SetReference(-38.83, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::armUp() {
    m_motorAngleLeftController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::teleOut() { 
    m_motorTelescopingController.SetReference(-134, rev::CANSparkMax::ControlType::kSmartMotion); // 137.43
}

void robotArm::teleIn() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::teleOutLong() {
    m_motorTelescopingController.SetReference(141.26, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::armDownLow() {
    m_motorAngleLeftController.SetReference(-34.69, rev::ControlType::kSmartMotion);
}

void robotArm::clampClose() {
    m_motorClamp.Set(0.5);
}

void robotArm::clampOpen() {
    m_motorClamp.Set(-0.5);
}

void robotArm::scoreLow() {
    // m_motorClamp.Set(0.5);
    m_motorAngleLeftController.SetReference(-22, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorTelescopingController.SetReference(78, rev::CANSparkMax::ControlType::kSmartMotion); //137.43

    while (m_encoderMotorTelescoping.GetPosition() < 76) { //135

    }

    m_motorAngleLeftController.SetReference(-30, rev::CANSparkMax::ControlType::kSmartMotion);
    // m_motorClamp.Set(-0.5);
}

void robotArm::scoreHigh() {
    // m_motorClamp.Set(0.5);
    m_motorAngleLeftController.SetReference(-22, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorTelescopingController.SetReference(138, rev::CANSparkMax::ControlType::kSmartMotion);

    while (m_encoderMotorTelescoping.GetPosition() < 136) {

    }

    m_motorAngleLeftController.SetReference(-30, rev::CANSparkMax::ControlType::kSmartMotion);
    // m_motorClamp.Set(-0.5);
}

void robotArm::Periodic() {
    frc::SmartDashboard::PutNumber("Tel Rel Enc Pos: ", m_encoderMotorTelescoping.GetPosition());
    frc::SmartDashboard::PutNumber("Tel Abs Enc Pos: ", m_encoderTelescoping.GetAbsolutePosition());

    // m_encoderMotorTelescoping.SetPosition(m_encoderTelescoping.GetAbsolutePosition());
    // m_encoderMotorTelescoping.SetPosition(0);
}