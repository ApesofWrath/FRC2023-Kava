
#include "subsystems/drivetrain.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

// Constructor, zeros the gyro for swervedrive
drivetrain::drivetrain() {
    m_navX.ZeroYaw();
}

// Resets the gyro when function run
void drivetrain::resetGyro() {
    m_navX.ZeroYaw();
}

// $ Slow constant value
void drivetrain::slowDown() {
    kslowConst = 0.5;
}

// Normal speed value (should always be 1.0)
void drivetrain::normalSpeed() {
    kslowConst = 1.0;
}

// Sets Desired States of the swerve modules for swervedrive
void drivetrain::SwerveDrive(units::meters_per_second_t xSpeed,
                             units::meters_per_second_t ySpeed,
                             units::radians_per_second_t zRot,
                             bool fieldRelative) {
    auto moduleStates = m_kinematics.ToSwerveModuleStates(
        fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(
                            xSpeed, ySpeed, zRot, m_navX.GetRotation2d())
                      : frc::ChassisSpeeds{xSpeed, ySpeed, zRot});
    m_kinematics.DesaturateWheelSpeeds(&moduleStates, drivetrainConstants::calculations::kModuleMaxSpeed);

    // frc::SmartDashboard::PutNumber("xSpeed", xSpeed.value());
    // frc::SmartDashboard::PutNumber("ySpeed", ySpeed.value());
    // frc::SmartDashboard::PutNumber("zRotation", zRot.value());
    // frc::SmartDashboard::PutNumber("Robot Position", m_navX.GetYaw());
    
    
    auto [frontRight, rearRight, frontLeft, rearLeft] = moduleStates;

    m_frontRight.SetDesiredState(frontRight);
    m_rearRight.SetDesiredState(rearRight);
    m_frontLeft.SetDesiredState(frontLeft);
    m_rearLeft.SetDesiredState(rearLeft);
}

// Updates the odometry of the swervedrive
void drivetrain::UpdateOdometry() {
    m_odometry.Update(m_navX.GetRotation2d() + frc::Rotation2d(180_deg), {m_frontRight.GetPosition(),
                      m_rearRight.GetPosition(), m_frontLeft.GetPosition(),
                      m_rearLeft.GetPosition()});
}

// Perodically (Constantly runs during periodic), updates the odometry of the swervedrive
frc::Pose2d drivetrain::GetOdometry() {
    return m_odometry.GetPose();
}

void drivetrain::ResetOdometry(frc::Pose2d initPose) {
    m_odometry.ResetPosition(m_navX.GetRotation2d() + frc::Rotation2d(180_deg), {m_frontRight.GetPosition(),
                      m_rearRight.GetPosition(), m_frontLeft.GetPosition(),
                      m_rearLeft.GetPosition()}, initPose);
}

std::string drivetrain::AutoBalance()
{
    if(m_navX.GetPitch() > 3.5)
    {
        return "Forward";
    }
    else if (m_navX.GetPitch() < -3.5)
    {
        return "Backward";
    }
    else
    {
        return "Stop";
    }
}

void drivetrain::Periodic() {
    UpdateOdometry();
    // Test posting angle to Dashboard.
    /* frc::SmartDashboard::PutNumber("Front Right Angle", m_frontRight.DashboardInfo(swerveModule::DataType::kCurrentAngle));
    frc::SmartDashboard::PutNumber("Rear Right Angle", m_rearRight.DashboardInfo(swerveModule::DataType::kCurrentAngle));
    frc::SmartDashboard::PutNumber("Front Left Angle", m_frontLeft.DashboardInfo(swerveModule::DataType::kCurrentAngle));
    frc::SmartDashboard::PutNumber("Rear Left Angle", m_rearLeft.DashboardInfo(swerveModule::DataType::kCurrentAngle));

    frc::SmartDashboard::PutNumber("Front Right TARGET", m_frontRight.DashboardInfo(swerveModule::DataType::kTargetAngle));
    frc::SmartDashboard::PutNumber("Rear Right TARGET", m_rearRight.DashboardInfo(swerveModule::DataType::kTargetAngle));
    frc::SmartDashboard::PutNumber("Front Left TARGET", m_frontLeft.DashboardInfo(swerveModule::DataType::kTargetAngle));
    frc:
    
    :SmartDashboard::PutNumber("Rear Left TARGET", m_rearLeft.DashboardInfo(swerveModule::DataType::kTargetAngle)); */
    // frc::SmartDashboard::PutNumber("Rear Left TARGET", m_rearLeft.DashboardInfo(swerveModule::DataType::kTargetAngle));
    frc::SmartDashboard::PutNumber("Odometry X", units::unit_cast<double>(m_odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Odometry Y", units::unit_cast<double>(m_odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Odometry Rot", units::unit_cast<double>(m_odometry.GetPose().Rotation().Degrees()));

    
}

void drivetrain::SimulationPeriodic() {}
