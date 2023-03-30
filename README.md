# FRC2023-Kava

Code for the FRC 2023 Season robot from Team 668, The Apes of Wrath, Kava!

Kava Features:
- A 4 Module Swerve Drivetrain with each module containing:
  - 1 REV Spark Max with a Neo Motor for turning and 1 for driving
  - A CanCoder Absolute Encoder for the turning motor
- A Robotic Arm with:
  - 1 REV Spark Max with a Neo for Opening and Closing the Clamp on top
  - 2 REV Spark Maxes with Neos for angling the arm up and down
  - 1 REV Spark Max with a Neo for telescoping the arm

Operator controlls:
  - [TBD]: Extend and angle down arm
  - [TBD]: Retract and angle up arm
Driver controlls:
  - Left analogue stick: Swerve movement
  - Right analogue stick: Rotate in place

Auton Selection Guide:
  - All paths start with the arm facing the grid
  - For any path name that begins with 'BumpCube' preload the cube somewhere on the bumpers so that it falls into the hybrid node as soon as the robot backs up
  - For any path name that begins with 'ScoreConeHigh' or 'ScoreConeMid' preload the cone into the claw using the method of turning the robot on so the motor goes into brake mode and then turning it back off as required and spinning the claw motor closed until it firmly clamps the cone and then letting it slowly back off
  - All paths that contain 'BalanceChargeStation' have an autobalance command at the end. All these paths should be started in front of the grid where there is only carpet in front of the robot, do not start them in areas where the cable bump or charge station is in front of the robot or the path will mess stuff up probably. Make sure to test autobalance before using.
  - 'NoBump' or 'CableBump' at the end indicates whether the robot should be started with the cable bump in front of it or not.
  - 'StraightLineTestX/Y' were test paths for testing at home that move 1 meter in their specific directions.
