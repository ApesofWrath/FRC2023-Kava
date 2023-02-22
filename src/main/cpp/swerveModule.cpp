#include "swerveModule.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/MathUtil.h>
#include <iostream>
#include <numbers>
#include <frc/geometry/Rotation2d.h>

swerveModule::swerveModule(const double module[]) 
    : m_motorDrive(module[0], rev::CANSparkMax::MotorType::kBrushless),
    m_motorTurn(module[1], rev::CANSparkMax::MotorType::kBrushless),
    m_encoderTurn(module[2]),
    m_encoderOffset(module[3]) {

    m_motorDrive.RestoreFactoryDefaults();
    m_motorTurn.RestoreFactoryDefaults();
    m_encoderTurn.ConfigFactoryDefault();

    m_motorDrive.SetInverted(true);
    m_motorTurn.SetInverted(true);

    m_motorDrive.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_motorTurn.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    m_motorDrive.SetSmartCurrentLimit(80.0);
    m_motorTurn.SetSmartCurrentLimit(20.0);

    m_encoderTurn.ConfigAllSettings(m_settings.encoderTurn);
    m_encoderTurn.ConfigMagnetOffset(m_encoderOffset);

    m_driveController.SetFeedbackDevice(m_encoderDrive);
    m_turnController.SetFeedbackDevice(m_encoderTurnIntegrated);

    m_driveController.SetP(0);
    m_driveController.SetI(0);
    m_driveController.SetD(0);
    m_driveController.SetFF(1/107.9101); //(0.5*1023.0)/(22100.0*0.5)
    m_driveController.SetOutputRange(-1.0F, 1.0F);

    m_turnController.SetP(0.015); //0.55
    m_turnController.SetI(0.0);
    m_turnController.SetD(0.001); //0.3
    m_turnController.SetFF(0.0);
    m_turnController.SetOutputRange(-1.0F, 1.0F);

    m_encoderTurnIntegrated.SetPositionConversionFactor(2.0 * 3.141592653589 * ((14.0 / 50.0) * (10.0 / 60.0)));
    m_encoderTurnIntegrated.SetVelocityConversionFactor((2.0 * 3.141592653589 * ((14.0 / 50.0) * (10.0 / 60.0))) / 60.0);

    m_encoderDrive.SetPositionConversionFactor(2.0 * 3.141592653589 * ((14.0 / 50.0) * (25.0 / 19.0) * (15.0 / 45.0)));
    m_encoderDrive.SetVelocityConversionFactor((2.0 * 3.141592653589 * ((14.0 / 50.0) * (25.0 / 19.0) * (15.0 / 45.0))) / 60.0);
}

/* void swerveModule::ConfigModule(const ConfigType& type) {
    switch(type) {
        case ConfigType::motorDrive :
            m_motorDrive.RestoreFactoryDefaults();
            //m_motorDrive.ConfigAllSettings(m_settings.motorDrive);
            //Bevel gear on left side.
            m_motorDrive.SetInverted(true); // counter clockwise
            m_motorDrive.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
            // m_motorDrive.SelectProfileSlot(0, 0);
            break;
        case ConfigType::motorTurn :
            m_motorTurn.RestoreFactoryDefaults();
            //m_motorTurn.ConfigAllSettings(m_settings.motorTurn);
            m_motorTurn.SetInverted(false); // clockwise
            m_motorTurn.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
            // m_motorTurn.SelectProfileSlot(0, 0);
            // m_motorTurn.ConfigRemoteFeedbackFilter(m_encoderTurn.GetDeviceNumber(),
            //                                        ctre::phoenix::motorcontrol::
            //                                        RemoteSensorSource::RemoteSensorSource_CANCoder, 0, 0);
            break;
        case ConfigType::encoderTurn :
            m_encoderTurn.ConfigFactoryDefault();
            m_encoderTurn.ConfigAllSettings(m_settings.encoderTurn);
            m_encoderTurn.ConfigMagnetOffset(m_encoderOffset);
            break;
        default :
            throw std::invalid_argument("Invalid swerveModule ConfigType");
    }
} */

/* frc::SwerveModuleState swerveModule::GetState() {
    units::native_units_per_decisecond_t motorSpeed{m_motorDrive.GetSelectedSensorVelocity(0)};
    units::meters_per_second_t wheelSpeed{
        (motorSpeed * drivetrainConstants::calculations::kWheelCircumference)
        / drivetrainConstants::calculations::kFinalDriveRatio};
    return {wheelSpeed,frc::Rotation2d(frc::AngleModulus(units::degree_t(m_encoderTurn.GetAbsolutePosition())))};
} */

frc::SwerveModulePosition swerveModule::GetPosition() {
    return {units::meter_t{m_encoderDrive.GetPosition()}, frc::Rotation2d(frc::AngleModulus(units::degree_t{m_encoderTurn.GetAbsolutePosition()}))};
}

void swerveModule::SetDesiredState(const frc::SwerveModuleState& referenceState) {
    const auto state = CustomOptimize(
        referenceState,units::degree_t(m_encoderTurn.GetAbsolutePosition()));
    //This returns the position in +-Cancoder units counting forever, as opposed to absolulte -180 to +180 deg.

    const auto targetWheelSpeed{state.speed};
    m_targetAngle = state.angle.Degrees().value();
    const double turnOutput = m_targetAngle; // (4096.0/360.0)

    units::radians_per_second_t targetMotorSpeed{
        (targetWheelSpeed * units::radian_t(2*3.14159))
        / drivetrainConstants::calculations::kWheelCircumference};
    
    //*m_motorDrive.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, targetMotorSpeed.value());
    m_driveController.SetReference(targetMotorSpeed.value(), rev::CANSparkMax::ControlType::kVelocity);
    // m_motorDrive.Set(ctre::phoenix::motorcontrol::ControlMode::Velocity, 0);
    //std::cout << targetMotorSpeed.value() << "-target_SPEED\n";

    //*m_motorTurn.SetSelectedSensorPosition(m_encoderTurn.GetPosition() * 4096/360);
    //m_encoderTurnIntegrated.SetPosition(m_encoderTurn.GetPosition());
    m_encoderTurnIntegrated.SetPosition(m_encoderTurn.GetAbsolutePosition());
    //*m_motorTurn.Set(ctre::phoenix::motorcontrol::TalonFXControlMode::Position, turnOutput);
    m_turnController.SetReference(turnOutput, rev::CANSparkMax::ControlType::kPosition);
    //m_motorTurn.Set(ctre::phoenix::motorcontrol::TalonFXControlMode::Position, 0);
    // m_motorTurn.Set(ctre::phoenix::motorcontrol::TalonFXControlMode::Position, 0);
    //std::cout << turnOutput << "u\n";

    frc::SmartDashboard::PutNumber("Target Wheel Speed", targetWheelSpeed.value());
    frc::SmartDashboard::PutNumber("Target Motor Speed", targetMotorSpeed.value());
}

frc::SwerveModuleState swerveModule::CustomOptimize(const frc::SwerveModuleState& desiredState,
                                                    const frc::Rotation2d& currentAngle) {
    auto modulusAngle{frc::AngleModulus(currentAngle.Degrees())};
    auto optAngle = desiredState.angle;
    auto optSpeed = desiredState.speed;
    
    auto difference = optAngle.Degrees() - modulusAngle;
    frc::SmartDashboard::PutNumber("Difference", difference.value());

    if (difference >= 270_deg) {
        difference = difference - 360_deg;
    } else if (difference <= -270_deg) {
        difference = difference + 360_deg;
    }

    if (units::math::abs(difference) > 90_deg) {
        optSpeed = -desiredState.speed;
        if (difference > 0_deg) {
            difference = difference - 180_deg;
        } else {
            difference = difference + 180_deg;
        }
    }
    optAngle = currentAngle.Degrees() + difference;

    frc::SmartDashboard::PutNumber("Desired Angle", optAngle.Degrees().value());

    frc::SmartDashboard::PutNumber("Neo Encoder Pos " + std::to_string(m_motorTurn.GetDeviceId()), m_encoderTurnIntegrated.GetPosition());
    frc::SmartDashboard::PutNumber("Neo Encoder Vel " + std::to_string(m_motorTurn.GetDeviceId()), m_encoderDrive.GetVelocity());
    //frc::SmartDashboard::PutNumber("Motor " + std::to_string(m_motorTurn.GetDeviceID()) + " Desired Angle", m_motorTurn.GetClosedLoopTarget());
    //frc::SmartDashboard::PutNumber("Motor " + std::to_string(m_motorTurn.GetDeviceID()) + " Real Angle", m_motorTurn.GetSelectedSensorPosition());

    return {optSpeed, optAngle};
}

double swerveModule::DashboardInfo(const DataType& type) {
    switch(type) {
        case DataType::kCurrentAngle :
            return {units::degree_t(frc::AngleModulus(units::degree_t(m_encoderTurn.GetAbsolutePosition()))).value()};
        /*case DataType::kCurrentVelocity :
            units::native_units_per_decisecond_t motorSpeed{m_motorDrive.GetSelectedSensorVelocity(0)};
            units::meters_per_second_t wheelSpeed{
                (motorSpeed * drivetrainConstants::calculations::kWheelCircumference)
                / drivetrainConstants::calculations::kFinalDriveRatio};
            return {wheelSpeed.value()};*/
        case DataType::kTargetAngle :
            return {m_targetAngle};
        default :
            throw std::invalid_argument("Invalid DashboardInfo DataType");
    }
}