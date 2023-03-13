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
/* m_encoderTelescoping(armConstants::arm::kRobotArm[4]), */
m_encoderOffset(armConstants::arm::kRobotArm[5]) {

    /* m_encoderTelescoping.ConfigMagnetOffset(m_encoderOffset);
    m_encoderTelescoping.ConfigMagnetOffset(m_encoderOffset);
    m_encoderTelescoping.ConfigSensorDirection(true); */

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

    m_motorAngleLeftController.SetSmartMotionMaxVelocity(5040); //7200
    m_motorAngleLeftController.SetSmartMotionMaxAccel(13400); //24800
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
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 40.0);

    m_motorClamp.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    m_motorClamp.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);

    m_motorAngleLeft.SetSmartCurrentLimit(40.0);
    m_motorAngleRight.SetSmartCurrentLimit(40.0);
    m_motorTelescoping.SetSmartCurrentLimit(40.0);

    m_motorTelescoping.SetInverted(false);

    m_motorAngleRight.Follow(m_motorAngleLeft, true);

    m_encoderMotorClamp.SetPosition(0);
}

void robotArm::armUp() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorAngleLeftController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);

}

void robotArm::clampToggle() {
    if (clawToggle == false) {
        m_motorClamp.Set(0.5);
        clawToggle = true;
    } else if (clawToggle == true) {
        m_motorClamp.Set(-0.5);
        clawToggle = false;
    } else {
        
    }
}

void robotArm::grabCone() {
    /* m_motorAngleLeftController.SetReference(-10, rev::ControlType::kSmartMotion);
    m_motorTelescopingController.SetReference(52, rev::ControlType::kSmartMotion);

    while (m_encoderMotorTelescoping.GetPosition() < 50) {

    }

    m_motorAngleLeftController.SetReference(-22, rev::ControlType::kSmartMotion); */

    currentStatePickup = ConePickupStates::FIRSTEXTEND;
}

void robotArm::scoreLow() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorAngleLeftController.SetReference(-42, rev::CANSparkMax::ControlType::kSmartMotion);
}

void robotArm::scoreMid() {
    /* m_motorAngleLeftController.SetReference(-22, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorTelescopingController.SetReference(80, rev::CANSparkMax::ControlType::kSmartMotion); //137.43

    while (m_encoderMotorTelescoping.GetPosition() < 78) { //135

    }

    m_motorAngleLeftController.SetReference(-30, rev::CANSparkMax::ControlType::kSmartMotion); */

    currentStateMid = ScoreMidStates::FIRSTEXTEND;
}

void robotArm::scoreHigh() {
    /* m_motorAngleLeftController.SetReference(-20, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorTelescopingController.SetReference(146, rev::CANSparkMax::ControlType::kSmartMotion);

    while (m_encoderMotorTelescoping.GetPosition() < 144) {

    }

    m_motorAngleLeftController.SetReference(-28, rev::CANSparkMax::ControlType::kSmartMotion); */

    currentStateHigh = ScoreHighStates::FIRSTEXTEND;
}

void robotArm::angleManualZero() {
    currentStateAngle = AngleStates::MANUALZERO;
    currentStateTele = TeleStates::MANUALZERO;
}

void robotArm::Periodic() {
    /* frc::SmartDashboard::PutNumber("Tel Rel Enc Pos: ", m_encoderMotorTelescoping.GetPosition());
    frc::SmartDashboard::PutNumber("Tel Abs Enc Pos: ", m_encoderTelescoping.GetAbsolutePosition());
    frc::SmartDashboard::PutNumber("L Angle Output Curr: ", m_motorAngleLeft.GetOutputCurrent());
 */
    switch (currentStateAngle) {
        case AngleStates::MANUALZERO:
            currentStateAngle = AngleStates::NOTZEROED;

            break;

        case AngleStates::INIT:
            m_motorAngleLeft.Set(0.05);
            if ((m_motorAngleLeft.GetOutputCurrent() + m_motorAngleRight.GetOutputCurrent()) > 10) {
                m_encoderMotorAngleLeft.SetPosition(0);
                currentStateAngle = AngleStates::ZEROED;
            }

            break;

        case AngleStates::NOTZEROED:
            currentStateAngle = AngleStates::INIT;

            break;

        case AngleStates::ZEROED:
            m_motorAngleLeft.Set(0.0);
            currentStateAngle = AngleStates::IDLE;
            break;

        default:
        case AngleStates::IDLE:

            break;
    }

    switch (currentStateTele) {
        case TeleStates::MANUALZERO:
            currentStateTele = TeleStates::NOTZEROED;

            break;

        case TeleStates::INIT:
            m_motorTelescoping.Set(-0.1);
            if (m_motorTelescoping.GetOutputCurrent() > 30) {
                m_encoderMotorTelescoping.SetPosition(0);
                currentStateTele = TeleStates::ZEROED;
            }

            break;

        case TeleStates::NOTZEROED:
            currentStateTele = TeleStates::INIT;

            break;

        case TeleStates::ZEROED:
            m_motorTelescoping.Set(0.0);
            currentStateTele = TeleStates::IDLE;
            break;

        default:
        case TeleStates::IDLE:

            break;
    }

    switch (currentStateHigh) {
        case ScoreHighStates::FIRSTEXTEND:
            m_motorAngleLeftController.SetReference(-20, rev::CANSparkMax::ControlType::kSmartMotion);
            m_motorTelescopingController.SetReference(144, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateHigh = ScoreHighStates::NOTHING;
            break;

        case ScoreHighStates::NOTHING:

            if (m_encoderMotorTelescoping.GetPosition() > 141) {
                currentStateHigh = ScoreHighStates::SECONDEXTEND;
            }
            break;

        case ScoreHighStates::SECONDEXTEND:
            m_motorAngleLeftController.SetReference(-28, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateHigh = ScoreHighStates::INIT;
            break;
            
        default:
        case ScoreHighStates::INIT:

            break;
    }

    switch (currentStateMid) {
        case ScoreMidStates::FIRSTEXTEND:
            m_motorAngleLeftController.SetReference(-22, rev::CANSparkMax::ControlType::kSmartMotion);
            m_motorTelescopingController.SetReference(80, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateMid = ScoreMidStates::NOTHING;
            break;

        case ScoreMidStates::NOTHING:

            if (m_encoderMotorTelescoping.GetPosition() > 77) {
                currentStateMid = ScoreMidStates::SECONDEXTEND;
            }
            break;

        case ScoreMidStates::SECONDEXTEND:
            m_motorAngleLeftController.SetReference(-30, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateMid = ScoreMidStates::INIT;
            break;

        default:
        case ScoreMidStates::INIT:

            break;
    }

    switch (currentStatePickup) {
        case ConePickupStates::FIRSTEXTEND:
            m_motorAngleLeftController.SetReference(-10, rev::ControlType::kSmartMotion);
            m_motorTelescopingController.SetReference(50, rev::ControlType::kSmartMotion);

            currentStatePickup = ConePickupStates::NOTHING;
            break;
            
        case ConePickupStates::NOTHING:

            if (m_encoderMotorTelescoping.GetPosition() > 47) {
                currentStatePickup = ConePickupStates::SECONDEXTEND;
            }
            break;

        case ConePickupStates::SECONDEXTEND:
            m_motorAngleLeftController.SetReference(-18, rev::ControlType::kSmartMotion);

            currentStatePickup = ConePickupStates::INIT;
            break;

        default:
        case ConePickupStates::INIT:

            break;
    }
}