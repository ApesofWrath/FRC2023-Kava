#pragma once

#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/time.h>
#include <units/velocity.h>
#include <numbers>

/**
 * This header contains hold robot-wide numerical or boolean constants ONLY.
 * 
 * Place constants into subsystem/command -specific NAMESPACES within this
 * header, which can then be included (where they are needed).
 */
namespace visionConstants {
    //How fast the robot attempts to correct its self
    constexpr double errorMultiplier = 0.05;
    //The minumum error for the robot to move
    constexpr double errorMinimum = 0.0;

    constexpr double xAlignMultiplier = 0.5;
    constexpr double zAlignMultiplier = -1.0;
    constexpr double yawAlignMultiplier = 0.0;
    // Robots distance from the April Tag it will align its self with
    constexpr double AlignDistance = -10.0;
    constexpr double rotationDistance = 1.0;
}

// IDs for controllers
namespace controllerConstants {
    //USB port addresses on drivestation PC.
    constexpr int kControllerMainID = 0;
    constexpr int kControllerAuxID = 1;
    // Curve amount for drivers controller
    constexpr double kControllerCurve = 8.0;
}

// Motor IDs for robot arm
 namespace armConstants {
    constexpr int kMotorArmAngleLeftID = 12;
    constexpr int kMotorArmAngleRightID = 13;
    constexpr int kMotorArmTelescopingID = 14;
    constexpr int kMotorArmClampID = 15;
    constexpr int kEncoderTelescopingID = 16;
    namespace offsets {
        constexpr double kTelescoping{-267.1};
    }
    namespace arm {
        constexpr double kRobotArm[6]{kMotorArmAngleLeftID,
                                        kMotorArmAngleRightID, 
                                        kMotorArmTelescopingID,
                                        kMotorArmClampID,
                                        kEncoderTelescopingID,
                                        offsets::kTelescoping};
    }
}

// Motor IDs, Encoder IDs, and Offsets for swervedrive
namespace drivetrainConstants {
    //CAN IDs
    constexpr int kMotorDriveFrontRightID = 26;
    constexpr int kMotorDriveRearRightID = 1;
    constexpr int kMotorDriveFrontLeftID = 2;
    constexpr int kMotorDriveRearLeftID = 3;

    constexpr int kMotorTurnFrontRightID = 4;
    constexpr int kMotorTurnRearRightID = 5;
    constexpr int kMotorTurnFrontLeftID = 6;
    constexpr int kMotorTurnRearLeftID = 7;

    constexpr int kEncoderTurnFrontRightID = 8;
    constexpr int kEncoderTurnRearRightID = 9;
    constexpr int kEncoderTurnFrontLeftID = 10;
    constexpr int kEncoderTurnRearLeftID = 11;

    namespace offsets {
        /* constexpr double kFrontRight{-38.057+180}; // tshirt shooter offsets
        constexpr double kRearRight{61.787};
        constexpr double kFrontLeft{38.057};
        constexpr double kRearLeft{3.164}; */

        constexpr double kFrontRight{50.713}; // curr robo offsets
        constexpr double kRearRight{154.160};
        constexpr double kFrontLeft{-6.416};
        constexpr double kRearLeft{89.912};
    }

    // Values for each swerve module object to use
    namespace swerveModules {
        constexpr double kModuleFrontRight[4]{kMotorDriveFrontRightID,
                                                   kMotorTurnFrontRightID,
                                                   kEncoderTurnFrontRightID,
                                                   offsets::kFrontRight};
        constexpr double kModuleRearRight[4]{kMotorDriveRearRightID,
                                                  kMotorTurnRearRightID,
                                                  kEncoderTurnRearRightID,
                                                  offsets::kRearRight};
        constexpr double kModuleFrontLeft[4]{kMotorDriveFrontLeftID,
                                                  kMotorTurnFrontLeftID,
                                                  kEncoderTurnFrontLeftID,
                                                  offsets::kFrontLeft};
        constexpr double kModuleRearLeft[4]{kMotorDriveRearLeftID,
                                                 kMotorTurnRearLeftID,
                                                 kEncoderTurnRearLeftID,
                                                 offsets::kRearLeft};
    }

    // Math constants and calculations to be used by swervedrive
    namespace calculations {
        constexpr auto kFinalDriveRatio{6.75 * 360_deg};
        constexpr auto kFinalTurnRatio{(14.0 / 50.0) * (10.0 / 60.0)};
        constexpr units::length::inch_t kWheelCircumference = {2 * std::numbers::pi * 3.8_in / 2};

        constexpr auto kModuleMaxSpeed{16.3_fps};
        constexpr auto kChassisMaxSpeed{16.3_fps};

        constexpr auto kModuleMaxAngularVelocity{std::numbers::pi * 4_rad_per_s};  // radians per second
        constexpr auto kModuleMaxAngularAcceleration{std::numbers::pi * 8_rad_per_s / 1_s};  // radians per second^2

        constexpr double kMotorMaxOutput = 0.5;
        constexpr double kMotorDeadband = 0.1;
    }
}
