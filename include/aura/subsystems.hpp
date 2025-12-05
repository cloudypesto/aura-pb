#pragma once
#include "main.h"
#include "pros/motors.hpp"


/**
*   This is where all the systems controlling the robot live
*   Contains:
*       - Drive Train
*       - Intake
*   
*   Idk prob will  have:
*       - outtake angle shifter
*       - matchload
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
        pros::IMU imu_2;


        public:

        //constructor
        drivetrain(int left_1_port, int left_2_port, int left_3_port, int left_4_port,
                    int right_1_port, int right_2_port, int right_3_port, int right_4_port,
                    char x_tracking_encoder_top, char x_tracking_encoder_bottom,
                    char y_tracking_encoder_top, char y_tracking_encoder_bottom,
                    int imu_1_port, int imu_2_port);


        //driver functions
        void driverFunctions();

        //helpers 
        void setDriveVoltage(double left_voltage, double right_voltage);

        void setBrakeMode(pros::motor_brake_mode_e brake_mode);

        
        //auton drive functions?

    };

    class intake{
        //set up the motors
        pros::Motor intake_top_1;
        pros::Motor intake_top_2;
        pros::Motor intake_bottom_1;
        pros::Motor intake_bottom_2;

        //set up the hood?
        pros::adi::Pneumatics intake_hood;

        //any like bools and stuff like to change setting like to switch to middle or somthing

        public:
        //constructor
        intake(int intake_top_1_port, int intake_top_2, int intake_bottom_1_port, int intake_bottom_2_port, char hood_solanoid_port);

        
        void setIntakeVoltage(double voltage);
        
        void driverFunctions();

        void autoFunctions(double voltage);

        void endAutoTask();


    };

    class matchload{
        pros::adi::Pneumatics matchload_solanoid;

        int matchload_press_count = 0;

        public:
        //constructor
        matchload(char matchload_solanoid_port);

        //function to set output
        void setState(bool matchloadState);

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



}