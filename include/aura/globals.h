#pragma once

/**
 * This is the File where all of the globals are set up
 * created to help simplify changing commonly used numbers and information
 * use negative to flip the port
 * Contains:
 *   - Drive Train
 *       - Wheel Sizes
 *       - Any sensor ports
 *       - Ports used
 *   - Any other subsystems Motor ports
 *   - Prenumatics ports
 */

// Drive Train
#define DRIVE_WHEEL_DIAMETER 2.75
#define DRIVE_GEAR_RATIO 0.75

// Track width
// distance between left and right wheel centers, meters (calibrate)
#define TRACKWIDTH 11.5

#define TRACKING_WHEEL_DIAMETER 3.25

#define HORIZONTAL_OFFSET 0.0
#define VERTICAL_OFFSET 0.0

// Motor ports
// left
#define LEFT_MOTOR_1 -1
#define LEFT_MOTOR_2 -2
#define LEFT_MOTOR_3 3
#define LEFT_MOTOR_4 -4

// right
#define RIGHT_MOTOR_1 5
#define RIGHT_MOTOR_2 6
#define RIGHT_MOTOR_3 -7
#define RIGHT_MOTOR_4 19

// encoding ports (currently not used)
//  #define X_ENCODER_TOP 'A'
//  #define X_ENCODER_BOTTOM 'B'
//  #define Y_ENCODER_TOP 'C'
//  #define Y_ENCODER_BOTTOM 'D'

// imu ports
#define IMU1 11

// Subsystems Motor ports

// set up so that they are all going up by default
// Intake
#define INTAKE_TOP_1 18
#define INTAKE_REDIR 9
#define INTAKE_BOTTOM_1 -10 // left
#define INTAKE_BOTTOM_2 8  // right

// Prenumatics ports

// Park
#define PARK 'X'

// Matchload
#define MATCHLOAD 'D'

// Intake
#define INAKE 'C'

// Hood / GATE
#define HOOD 'A'

// Wing
#define DESCORE 'B'
