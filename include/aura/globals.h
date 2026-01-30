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
#define LEFT_MOTOR_1 -11
#define LEFT_MOTOR_2 -12
#define LEFT_MOTOR_3 13
#define LEFT_MOTOR_4 -14

// right
#define RIGHT_MOTOR_1 17
#define RIGHT_MOTOR_2 16
#define RIGHT_MOTOR_3 -18
#define RIGHT_MOTOR_4 20

// encoding ports (currently not used)
//  #define X_ENCODER_TOP 'A'
//  #define X_ENCODER_BOTTOM 'B'
//  #define Y_ENCODER_TOP 'C'
//  #define Y_ENCODER_BOTTOM 'D'

// imu ports
#define IMU1 15

// Subsystems Motor ports

// set up so that they are all going up by default
// Intake
#define INTAKE_TOP_1 19
#define INTAKE_REDIR 10
#define INTAKE_BOTTOM_1 -1 // left
#define INTAKE_BOTTOM_2 9  // right

// Prenumatics ports

// Park
#define PARK 'X'

// Matchload
#define MATCHLOAD 'A' 

// Intake
#define INAKE 'C' 

// Hood / GATE
#define HOOD 'B' 

// Wing
#define DESCORE 'X'
