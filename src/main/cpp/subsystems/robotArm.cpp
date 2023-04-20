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

    // Set limits for position on the arm angling motors (not telescoping)
    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 4.0);
    m_motorAngleLeft.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, -38.0);
    
    // Sets current limit for the clamp motor on the arm, sets the motors direction inverted, and sets position limits for the motor

    // $ CURRENT LIMIT OF CLAMP
    m_motorClamp.SetSmartCurrentLimit(2.0);

    // $ SETS CLAMP INVERTED OR NOT
    m_motorClamp.SetInverted(true);

    // $ FORWARD LIMIT OF CLAMP
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kReverse, 5.0);

    // $ REVERSE LIMIT OF CLAMP
    m_motorClamp.SetSoftLimit(rev::CANSparkMax::SoftLimitDirection::kForward, 32.0);

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

    // TELESCOPING MOTOR CONVERTION FACTORS, PID, SMARTMOTION
    // ***
    // ***
    m_encoderMotorTelescoping.SetPositionConversionFactor((1.0 / armConstants::kRotationsToInchTelescoping) * (1.0 / 39.37));
    m_encoderMotorTelescoping.SetVelocityConversionFactor(((1.0 / armConstants::kRotationsToInchTelescoping) * (1.0 / 39.37)) / 60.0);

    // Velocity values for the telescoping motor
    m_motorTelescopingController.SetSmartMotionMaxVelocity(1.5); //8400
    m_motorTelescopingController.SetSmartMotionMaxAccel(0.75); //17200
    m_motorTelescopingController.SetSmartMotionMinOutputVelocity(0); //0
    m_motorTelescopingController.SetSmartMotionAllowedClosedLoopError(0.01); //0

    // PID constants for the telescoping motor
    m_motorTelescopingController.SetP(0.0001);
    m_motorTelescopingController.SetI(0);
    m_motorTelescopingController.SetD(0);
    m_motorTelescopingController.SetFF(1.0/5767.0/(((1.0 / armConstants::kRotationsToInchTelescoping) * (1.0 / 39.37)) / 60.0));
    m_motorTelescopingController.SetOutputRange(-1.0F, 1.0F);

    // ANGLING MOTOR CONVERSION FACTORS, PID, SMARTMOTION
    // ***
    // ***
    m_encoderMotorAngleLeft.SetPositionConversionFactor((1.0 / armConstants::kRotationsToRadianAngling));
    m_encoderMotorAngleLeft.SetVelocityConversionFactor((1.0 / armConstants::kRotationsToRadianAngling) / 60.0);

    // Velocity values for the arm angling motors (not telescoping)
    m_motorAngleLeftController.SetSmartMotionMaxVelocity(7); //7200; 5040.0 * (1.0 / armConstants::kRotationsToRadianAngling) / 60.0
    m_motorAngleLeftController.SetSmartMotionMaxAccel(4); //24800; 6700.0 *(1.0 / armConstants::kRotationsToRadianAngling) / 60.0
    m_motorAngleLeftController.SetSmartMotionMinOutputVelocity(0); //0
    m_motorAngleLeftController.SetSmartMotionAllowedClosedLoopError(0); //0

    // PID constants for position control for the arm angling up and down (not telescoping)
    m_motorAngleLeftController.SetP(0.05); // 0.00005; 0.5 / armConstants::kRotationsToRadianAngling
    m_motorAngleLeftController.SetI(0);
    m_motorAngleLeftController.SetD(0); // (0.005 / armConstants::kRotationsToRadianAngling) * 10
    m_motorAngleLeftController.SetFF((1.0 / 2.359) * 0.1);
    m_motorAngleLeftController.SetOutputRange(-1.0F, 1.0F);
}

/* units::meter_t toMeters(int encRotations) {
    return {units::meter_t{(encRotations / armConstants::kRotationsToInchTelescoping) / 39.37}};
} */

// Sets the position of the arm and telescoping motors to 0 to put the arm in a retracted up state
void robotArm::armUp() {
    m_motorTelescopingController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
    m_motorAngleLeftController.SetReference(0, rev::CANSparkMax::ControlType::kSmartMotion);
}

// Opens and closes the clamp with a toggle boolean
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
    m_motorAngleLeftController.SetReference(-1.03083, rev::CANSparkMax::ControlType::kSmartMotion);
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

/* void robotArm::setArmAngle(double angle){
    currScoreSecAngle = angle;
}

void robotArm::setArmLength(double length){
    currScoreLength = length;
} */

void robotArm::setArmPos(double angle, double length) {
    currScoreSecAngle = angle;
    currScoreLength = length;

    currentStateVision = ScoreVisionStates::FIRSTEXTEND;
}

// All code in this function runs continuosly as the robot is running in Periodic
void robotArm::Periodic() {
    
    // Says whether clamp is open or closed in smartdashboard
    frc::SmartDashboard::PutBoolean("Clamp Closed?", clawToggle);

    frc::SmartDashboard::PutNumber("Tele Pos", m_encoderMotorTelescoping.GetPosition());
    frc::SmartDashboard::PutNumber("Angle Pos", m_encoderMotorAngleLeft.GetPosition());

    frc::SmartDashboard::PutNumber("Target Angle", currScoreSecAngle);
    frc::SmartDashboard::PutNumber("Target Length", currScoreLength);

    // ZEROING state machine for the arm angle position
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

    // ZEROING state machine for the telescoping position
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

    // $ state machine for moving the arm to a position to score the cone in a HIGH POSITION
    switch (currentStateHigh) {
        case ScoreHighStates::FIRSTEXTEND:
            // First time arm angles down
            m_motorAngleLeftController.SetReference(-0.58905, rev::CANSparkMax::ControlType::kSmartMotion); // -24
            // Sets telescope position to telescope out for scoring
            m_motorTelescopingController.SetReference(1.04959, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateHigh = ScoreHighStates::NOTHING;
            break;

        case ScoreHighStates::NOTHING:

            // Waits until telescope reaches its position (if statement value should be 3 less than actual position)
            if (m_encoderMotorTelescoping.GetPosition() > 1.027259) {
                currentStateHigh = ScoreHighStates::SECONDEXTEND;
            }
            break;

        case ScoreHighStates::SECONDEXTEND:
            // After telescope reaches its position, arm angles down more to its socring position
            m_motorAngleLeftController.SetReference(-0.78540, rev::CANSparkMax::ControlType::kSmartMotion); // -32

            currentStateHigh = ScoreHighStates::INIT;
            break;
            
        default:
        case ScoreHighStates::INIT:

            break;
    }

    // $ state machine for moving the arm to a position to score the cone in the MIDDLE POSITION
    switch (currentStateMid) {
        case ScoreMidStates::FIRSTEXTEND:
            // First time arm angles down
            m_motorAngleLeftController.SetReference(-0.58905, rev::CANSparkMax::ControlType::kSmartMotion); // -24
            // Sets telescope position to telescope out for scoring
            m_motorTelescopingController.SetReference(0.58063, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateMid = ScoreMidStates::NOTHING;
            break;

        case ScoreMidStates::NOTHING:
            // Waits until telescope reaches its position (if statement value should be 3 less than actual position)
            if (m_encoderMotorTelescoping.GetPosition() > 0.55829) {
                currentStateMid = ScoreMidStates::SECONDEXTEND;
            }
            break;

        case ScoreMidStates::SECONDEXTEND:
            // After telescope reaches its position, arm angles down more for scoring position
            m_motorAngleLeftController.SetReference(-0.78540, rev::CANSparkMax::ControlType::kSmartMotion); // -32

            currentStateMid = ScoreMidStates::INIT;
            break;

        default:
        case ScoreMidStates::INIT:

            break;
    }

    // $ state machine to move the arm to a position to PICK UP the CONE from the HUMAN PLAYER
    switch (currentStatePickup) {
        case ConePickupStates::FIRSTEXTEND:
            // First time arm angles down
            m_motorAngleLeftController.SetReference(-0.24544, rev::ControlType::kSmartMotion); // -10
            // Sets telescope position to telescope out for scoring
            m_motorTelescopingController.SetReference(0.33498, rev::ControlType::kSmartMotion);

            currentStatePickup = ConePickupStates::NOTHING;
            break;
            
        case ConePickupStates::NOTHING:
            // Waits until telescope reaches its position (if statement value should be 1 less than actual value)
            if (m_encoderMotorTelescoping.GetPosition() > 0.32753) {
                currentStatePickup = ConePickupStates::SECONDEXTEND;
            }
            break;

        case ConePickupStates::SECONDEXTEND:
            // After telescope reaches its position, arm angles down more to its scoring position
            m_motorAngleLeftController.SetReference(-0.61360, rev::ControlType::kSmartMotion); // -25

            currentStatePickup = ConePickupStates::INIT;
            break;

        default:
        case ConePickupStates::INIT:

            break;
    }

    switch (currentStateVision) {
        case ScoreVisionStates::FIRSTEXTEND:
            // First time arm angles down
            m_motorAngleLeftController.SetReference(-0.58905, rev::CANSparkMax::ControlType::kSmartMotion); // -24
            // Sets telescope position to telescope out for scoring
            m_motorTelescopingController.SetReference(0.848 * currScoreLength, rev::CANSparkMax::ControlType::kSmartMotion);

            currentStateVision = ScoreVisionStates::NOTHING;
            break;

        case ScoreVisionStates::NOTHING:

            // Waits until telescope reaches its position (if statement value should be 3 less than actual position)
            if (m_encoderMotorTelescoping.GetPosition() > ((0.848 * currScoreLength) - 0.03)) {
                currentStateVision = ScoreVisionStates::SECONDEXTEND;
            }

            break;

        case ScoreVisionStates::SECONDEXTEND:
            // After telescope reaches its position, arm angles down more to its socring position
            m_motorAngleLeftController.SetReference(currScoreSecAngle, rev::CANSparkMax::ControlType::kSmartMotion); // -32

            currentStateVision = ScoreVisionStates::INIT;
            break;
            
        default:
        case ScoreVisionStates::INIT:

            break;
    }
}