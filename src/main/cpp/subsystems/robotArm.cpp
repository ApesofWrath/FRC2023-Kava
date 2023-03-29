#pragma once
#include "subsystems/robotArm.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/MathUtil.h>
#include <iostream>
#include <numbers>
#include <frc/geometry/Rotation2d.h>

// Constructor for robot arm, creates all the motors and configures their settings
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

    // Reset all motors to factory default settings
    m_motorAngleLeft.RestoreFactoryDefaults();
    m_motorAngleRight.RestoreFactoryDefaults();
    m_motorTelescoping.RestoreFactoryDefaults();
    m_motorClamp.RestoreFactoryDefaults();
 
    // Sets idle mode of the motors to Brake (motors breake while not doing anything)
    m_motorAngleLeft.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_motorAngleRight.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_motorClamp.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    // Sets the encoder the motors use for positioning to the built in motor encoders
    m_motorAngleLeftController.SetFeedbackDevice(m_encoderMotorAngleLeft);
    m_motorTelescopingController.SetFeedbackDevice(m_encoderMotorTelescoping);

    // PID constants for position control for the arm angling up and down (not telescoping)
    m_motorAngleLeftController.SetP(0.00005);
    m_motorAngleLeftController.SetI(0);
    m_motorAngleLeftController.SetD(0);
    m_motorAngleLeftController.SetFF(1.0/5767.0);
    m_motorAngleLeftController.SetOutputRange(-1.0F, 1.0F);

    // Set limits for position on the arm angling motors (not telescoping)
    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 4.0);
    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, -38.0);

    // Velocity values for the arm angling motors (not telescoping)
    m_motorAngleLeftController.SetSmartMotionMaxVelocity(5040); //7200
    m_motorAngleLeftController.SetSmartMotionMaxAccel(13400); //24800
    m_motorAngleLeftController.SetSmartMotionMinOutputVelocity(0); //0
    m_motorAngleLeftController.SetSmartMotionAllowedClosedLoopError(0); //0

    // PID constants for the telescoping motor
    m_motorTelescopingController.SetP(0);
    m_motorTelescopingController.SetI(0);
    m_motorTelescopingController.SetD(0);
    m_motorTelescopingController.SetFF(1.0/5767.0);
    m_motorTelescopingController.SetOutputRange(-1.0F, 1.0F);

    // Velocity values for the telescoping motor
    m_motorTelescopingController.SetSmartMotionMaxVelocity(8400); //2400
    m_motorTelescopingController.SetSmartMotionMaxAccel(17200); //9600
    m_motorTelescopingController.SetSmartMotionMinOutputVelocity(0); //0
    m_motorTelescopingController.SetSmartMotionAllowedClosedLoopError(0); //0

    // Sets current limit for the clamp motor on the arm, sets the motors direction inverted, and sets position limits for the motor

    // $ CURRENT LIMIT OF CLAMP
    m_motorClamp.SetSmartCurrentLimit(1.0);

    // $ SETS CLAMP INVERTED OR NOT
    m_motorClamp.SetInverted(true);

    // $ FORWARD LIMIT OF CLAMP
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 5.0);

    // $ REVERSE LIMIT OF CLAMP
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 30.0);

    // Just enables the position limits for the clamp motor
    m_motorClamp.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, true);
    m_motorClamp.EnableSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, true);

    // Sets current limits for the arm angling motors and the telescoping motor
    m_motorAngleLeft.SetSmartCurrentLimit(40.0);
    m_motorAngleRight.SetSmartCurrentLimit(40.0);
    m_motorTelescoping.SetSmartCurrentLimit(40.0);

    // Sets the motor direction of the telescoping motor to not being inverted
    m_motorTelescoping.SetInverted(false);

    // Sets the right arm angling motor to follow the direction of the left arm angling motor
    m_motorAngleRight.Follow(m_motorAngleLeft, true);

    // Sets position of the clamp motor when the robot boots to 0
    m_encoderMotorClamp.SetPosition(0);
}

// Sets the position of the arm and telescoping motors to 0 to put the arm in a retracted up state
void robotArm::armUp() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorAngleLeftController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
}

// Opens and closes the clamp with a toggle
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

// Sets the first state of the cone pickup state machine so the robot arm is in position to pick up a cone from the human player
void robotArm::grabCone() {
    currentStatePickup = ConePickupStates::FIRSTEXTEND;
}

// Sets the arm to a low position to score cones in the lowest position
void robotArm::scoreLow() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorAngleLeftController.SetReference(-42, rev::CANSparkMax::ControlType::kSmartMotion);
}

// Sets the first state of the score cone middle state machine so the robot arm is in position to score a cone in the middle positon
void robotArm::scoreMid() {
    currentStateMid = ScoreMidStates::FIRSTEXTEND;
}

// Sets the first state of the score cone high state machine so the robot arm is in position to score a cone in the high position
void robotArm::scoreHigh() {
    currentStateHigh = ScoreHighStates::FIRSTEXTEND;
}

// Sets the first states of the zeroing state machines for zeroing the telescope and the arm angle position
void robotArm::angleManualZero() {
    currentStateAngle = AngleStates::MANUALZERO;
    currentStateTele = TeleStates::MANUALZERO;
}

// All code in this function runs continuosly as the robot is running in Periodic
void robotArm::Periodic() {

    // zeroing state machine for the arm angle position
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

    // zeroing state machine for the telescoping position
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

    // state machine for moving the arm to a position to score the cone in a high position
    switch (currentStateHigh) {
        case ScoreHighStates::FIRSTEXTEND:
            m_motorAngleLeftController.SetReference(-20, rev::CANSparkMax::ControlType::kSmartMotion);
            m_motorTelescopingController.SetReference(141, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateHigh = ScoreHighStates::NOTHING;
            break;

        case ScoreHighStates::NOTHING:

            if (m_encoderMotorTelescoping.GetPosition() > 138) {
                currentStateHigh = ScoreHighStates::SECONDEXTEND;
            }
            break;

        case ScoreHighStates::SECONDEXTEND:
            m_motorAngleLeftController.SetReference(-32, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateHigh = ScoreHighStates::INIT;
            break;
            
        default:
        case ScoreHighStates::INIT:

            break;
    }

    // state machine for moving the arm to a position to score the cone in the middle position
    switch (currentStateMid) {
        case ScoreMidStates::FIRSTEXTEND:
            m_motorAngleLeftController.SetReference(-22, rev::CANSparkMax::ControlType::kSmartMotion);
            m_motorTelescopingController.SetReference(78, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateMid = ScoreMidStates::NOTHING;
            break;

        case ScoreMidStates::NOTHING:

            if (m_encoderMotorTelescoping.GetPosition() > 75) {
                currentStateMid = ScoreMidStates::SECONDEXTEND;
            }
            break;

        case ScoreMidStates::SECONDEXTEND:
            m_motorAngleLeftController.SetReference(-32, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateMid = ScoreMidStates::INIT;
            break;

        default:
        case ScoreMidStates::INIT:

            break;
    }

    // state machine to move the arm to a position to pick up the cone from the human player
    switch (currentStatePickup) {
        case ConePickupStates::FIRSTEXTEND:
            m_motorAngleLeftController.SetReference(-10, rev::ControlType::kSmartMotion);
            m_motorTelescopingController.SetReference(45, rev::ControlType::kSmartMotion);

            currentStatePickup = ConePickupStates::NOTHING;
            break;
            
        case ConePickupStates::NOTHING:

            if (m_encoderMotorTelescoping.GetPosition() > 44) {
                currentStatePickup = ConePickupStates::SECONDEXTEND;
            }
            break;

        case ConePickupStates::SECONDEXTEND:
            m_motorAngleLeftController.SetReference(-25, rev::ControlType::kSmartMotion);

            currentStatePickup = ConePickupStates::INIT;
            break;

        default:
        case ConePickupStates::INIT:

            break;
    }
}