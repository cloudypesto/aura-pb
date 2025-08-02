#pragma once
#include "main.h"

namespace subsystems {

    class drivetrain {
        pros::Motor left_1;
        pros::Motor left_2;
        pros::Motor left_3;
        pros::Motor left_4;

        pros::Motor right_1;
        pros::Motor right_2;
        pros::Motor right_3;
        pros::Motor right_4;

        pros::MotorGroup leftDrive = pros::MotorGroup(left_1);
        pros::MotorGroup rightDrive = pros::MotorGroup(right_1);

        pros::adi::Encoder XTrackingEncoder;
        pros::adi::Encoder YTrackingEncoder;

        pros::IMU imu_1;
        pros::IMU imu_2;

        public:
        
        //constructor 
        drivetrain (int left_1_port, int left_2_port, int left_3_port, int left_4_port,
                    int right_1_port, int right_2_port, int right_3_port, int right_4_port,
                    char x_tracking_encoder_top, char x_tracking_encoder_bottom,
                    char y_tracking_encoder_top, char y_tracking_encoder_bottom,
                    int imu_1_port, int imu_2_port);
    
        //driver functions
        void driverFunctions();

        //helpers
        void setDriveVoltage(double left_voltage, double right_voltage);
        void setBrakeMode(pros::motor_brake_mode_e brake_mode);
    
    };


    
}//namespace subsystems