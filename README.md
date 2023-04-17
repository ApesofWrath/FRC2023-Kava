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

Operator controls:
  - [TBD]: Extend and angle down arm
  - [TBD]: Retract and angle up arm
Driver controls:
  - Left analogue stick: Swerve movement
  - Right analogue stick: Rotate in place

Auto Selection Guide:
  - All paths start with the arm facing the grid
  - Select the start behavior from its respective chooser. It should only have something like 3 options, if there is more it is likely the path chooser
  - Select the path from its respective chooser. It should have more options than the start behavior chooser(NOTE: The paths are only named for what actually happens during them. For example, a path that starts with "1ConeAuto" will only pick up and score 1 cone in the path, however 2 cones may be scored in that auto if the start behavior scores a cone in addition to the path)
  - "Bump" or "NoBump" refers to whether the auto should be run on the side of the field with the cable bump or not.
  - Path names that end with "Balance" or "AutoBalance" attempt to balance on the charge station at the end of auto
  - If a path name is confusing, open up the actual pathplanner program and take a look at that path to see what it looks like and should do.
