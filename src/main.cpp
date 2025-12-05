#include "main.h"
#include "../include/aura/globals.h"
//create the drive train
subsystems::drivetrain drivetrain = subsystems::drivetrain
(   LEFT_MOTOR_1,
	LEFT_MOTOR_2,
	LEFT_MOTOR_3,
	LEFT_MOTOR_4,
	RIGHT_MOTOR_1,
	RIGHT_MOTOR_2,
	RIGHT_MOTOR_3,
	RIGHT_MOTOR_4,
	'A',
	'B',
	'C',
	'D', 
	IMU1,
	IMU2
);


//create other sub systems

//set up intake


//set up match load

//set up descore


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "your mom!");


	//calabrate the imu when starting the program
	pros::IMU imu1 = pros::IMU(IMU1);
	pros::IMU imu2 = pros::IMU(IMU2);

	
    imu1.reset();
	imu2.reset();
}

void disabled() {}


void competition_initialize() {}


void autonomous() {
	
}


void opcontrol() {

	//end anything being used in auton
	drivetrain.setBrakeMode(MOTOR_BRAKE_COAST);

	while(true){
		//run all the driver functions and anything that needs to be constantly running
		drivetrain.driverFunctions();


	pros::delay(10);
	}
}