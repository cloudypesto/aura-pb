#include "main.h"
#include "../include/aura/globals.h"
#include "aura/subsystems.hpp"
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
subsystems::intake intake = subsystems::intake(INTAKE_TOP_1,
												INTAKE_REDIR,
												INTAKE_BOTTOM_1,
												INTAKE_BOTTOM_1,
												HOOD,
												INAKE1,
											INAKE2);


//set up match load
subsystems::matchload matchload = subsystems::matchload(MATCHLOAD);

//set up descore
subsystems::descore descore = subsystems::descore(DESCORE);

//set up park
subsystems::park park = subsystems::park(PARK1,PARK2);



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
		//control drive
		drivetrain.driverFunctions();
		//control intake
		intake.driverFunctions();
        //matchloader
        matchload.driverFunctions();
        //descore
        descore.driverFunctions();
		//park
		park.driverFunctions();


	pros::delay(10);
	}
}