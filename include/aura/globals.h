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
        #define X_ENCODER_TOP 'A'
        #define X_ENCODER_BOTTOM 'B'
        #define Y_ENCODER_TOP 'C'
        #define Y_ENCODER_BOTTOM 'D'

    //imu ports
        #define IMU1 11
        #define IMU2 20



//Subsystems Motor ports

    //Intake
    #define INTAKE_TOP_1 6
    #define INTAKE_TOP_2 5
    #define INTAKE_BOTTOM_1 16
    #define INTAKE_BOTTOM_2 14




//Prenumatics ports
    
    //Hood
    #define HOOD 'E'

    //Front roller
    //I think this has 2?

    //Matchload
    #define MATCHLOAD 'F'

    //Wing
    #define DESCORE 'H'

    //Angleshifter




