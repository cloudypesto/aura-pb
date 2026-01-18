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

//Drive Train
    #define DRIVE_WHEEL_DIAMETER 3.25
    #define DRIVE_GEAR_RATIO 0.75

    //Track width
    //distance between left and right wheel centers, meters (calibrate)
    #define TRACKWIDTH 10.5

    #define TRACKING_WHEEL_DIAMETER 3.25

    #define HORIZONTAL_OFFSET 0.0
    #define VERTICAL_OFFSET 0.0



    //Motor ports
    //left
        #define LEFT_MOTOR_1 -9
        #define LEFT_MOTOR_2 8
        #define LEFT_MOTOR_3 -10
        #define LEFT_MOTOR_4 7
        
    //right
        #define RIGHT_MOTOR_1 3
        #define RIGHT_MOTOR_2 -4
        #define RIGHT_MOTOR_3 2
        #define RIGHT_MOTOR_4 -1

    //encoding ports (currently not used)
        // #define X_ENCODER_TOP 'A'
        // #define X_ENCODER_BOTTOM 'B'
        // #define Y_ENCODER_TOP 'C'
        // #define Y_ENCODER_BOTTOM 'D'

    //imu ports
        #define IMU1 20



//Subsystems Motor ports

    //Intake
    #define INTAKE_TOP_1 -1
    #define INTAKE_REDIR 10
    #define INTAKE_BOTTOM_1 -11
    #define INTAKE_BOTTOM_2 20



//Prenumatics ports
    
    //Park
    #define PARK 'A'

    //Matchload
    #define MATCHLOAD 'C'

    //Intake
    #define INAKE 'D'

    //Hood / GATE
    #define HOOD 'F'

    //Wing
    #define DESCORE 'G'






