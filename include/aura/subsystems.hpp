#pragma once
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "globals.h"



/**
*   This is where all the systems controlling the robot live
*   Contains:
*       - Drive Train
*       - Intake
*       - Match load
*       - Descore
*       - Park
*/


namespace subsystems {
    class drivetrain{
        //set up the motors used in the drivetrain
        //numbered
        pros::Motor left_1;
        pros::Motor left_2;
        pros::Motor left_3;
        pros::Motor left_4;

        pros::Motor right_1;
        pros::Motor right_2;
        pros::Motor right_3;
        pros::Motor right_4;

        //group them together so they are able to run togther
        //the rest get added to the group after set up
        pros::MotorGroup leftDrive = pros::MotorGroup(left_1);
        pros::MotorGroup rightDrive = pros::MotorGroup(right_1);

        //set up encoder tracking
        pros::adi::Encoder XTrackingEncoder;
        pros::adi::Encoder YTrackingEncoder;

        //set up IMU
        pros::IMU imu_1;
        


        bool odomRunning = false;


        public:
        //allows for getting the motor data for lemlib to use
        //motor gorup getters
        pros::MotorGroup& getLeftDrive() { return leftDrive; }
        pros::MotorGroup& getRightDrive() { return rightDrive; }

        //tracking wheels getters
        pros::adi::Encoder& getXTrackingEncoder() { return XTrackingEncoder; }
        pros::adi::Encoder& getYTrackingEncoder() { return YTrackingEncoder; }

        //imu getter
        pros::IMU& getIMU() { return imu_1; }

        //constructor
        drivetrain(int left_1_port, int left_2_port, int left_3_port, int left_4_port,
                    int right_1_port, int right_2_port, int right_3_port, int right_4_port,
                    char x_tracking_encoder_top, char x_tracking_encoder_bottom,
                    char y_tracking_encoder_top, char y_tracking_encoder_bottom,
                    int imu_1_port);


        //driver functions
        void driverFunctions();

        //helpers 
        void setDriveVoltage(double left_voltage, double right_voltage);

        void setBrakeMode(pros::motor_brake_mode_e brake_mode);

        

        //Movement helper functions for autonomous
        //temp functions casue like we need to be able to go stright for now
        void moveDistance(double inches, double speed, int timeout);
        
        

    };

    //used to set the state of the intake
    enum IntakeMode {
        IDLE,
        INTAKE_INDEX,
        OUTTAKE_LOW,
        SCORE_TALL,
        SCORE_MID,
        UNJAM
    };
    
    class intake{
        //set up the motors
        pros::Motor intake_top_1;
        pros::Motor redir;
        pros::Motor intake_bottom_1;
        pros::Motor intake_bottom_2;

        //set up the hood
        pros::adi::Pneumatics intake_hood;

        //used to lift the intake up and down
        //uses 2 pistons
        pros::adi::Pneumatics intake_solanoid;

        //any like bools and stuff like to change setting like to switch to middle or somthing
        int intake_press_count = 0;

        int hood_press_count = 0;

        //be able to ge between the modes when diffrent buttons pressed
        IntakeMode currentMode = IDLE;

        //allow the index to keep running
        bool indexingEnabled = false;

        

        //allow the mid to be ran fast
        bool midFast = false;

        //allow the low to be ran slowly
        bool lowFast = false;

        int32_t unjamStartTime = 0;
        static constexpr int32_t UNJAM_TIME = 333;


        
        public:
        //constructor
        intake(int intake_top_1_port, 
                int redir_port, 
                int intake_bottom_1_port, 
                int intake_bottom_2_port, 
                char hood_solanoid_port, 
                char intake_solanoid_port);

        //combining these into one thing so it sets the sate for all of them
        // void setIntakeVoltage(double voltage);

        // void setIntakeState(bool intake_state);

        // void setHoodState(bool hood_state);
        
        //sets the intake voltage and the states for all the pistons
        void setIntakeState(double lower_voltage, 
                            double redir_voltage,
                            double upper_voltage, 
                            bool hood_solanoid_state, 
                            bool intake_solanoid_state);

        
        void driverFunctions();

        //auton intake
        void autoPickUP(double speed);

        void autoScoreHigh(double speed);

        void autoScoreLow(double speed);

        void autoScoreMid(double speed);

        void stopAuto();


    };

    class matchload{
        pros::adi::Pneumatics matchload_solanoid;

        int matchload_press_count = 0;

        public:
        //constructor
        matchload(char matchload_solanoid_port);

        //function to set output
        void setState(bool matchload_state);

        //function to run during driver control
        void driverFunctions();

    };

    class descore
    {
        pros::adi::Pneumatics descore_solanoid;

        int pressCount = 0;

        public:
        //Constructor
        descore(char descore_solanoid_port);

        //Function to set output
        void setState(bool state);

        //Function to run during driver control
        void driverFunctions();
    };


    class park{
        pros::adi::Pneumatics park_solanoid;

        int press_count = 0;

        public:
        //constructor
        park(char park_solanoid_port);

        //Function to set output
        void setState(bool state);

        //Function to run during driver control
        void driverFunctions();


    };


}