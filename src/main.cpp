#include "main.h"
#include "../include/aura/globals.h"
#include "aura/subsystems.hpp"

#include "aura/lemlib.hpp"



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
	IMU1
);


//create other sub systems

//set up intake
subsystems::intake intake = subsystems::intake(INTAKE_TOP_1,
												INTAKE_REDIR,
												INTAKE_BOTTOM_1,
												INTAKE_BOTTOM_1,
												HOOD,
												INAKE);


//set up match load
subsystems::matchload matchload = subsystems::matchload(MATCHLOAD);

//set up descore
subsystems::descore descore = subsystems::descore(DESCORE);

//set up park
subsystems::park park = subsystems::park(PARK);



void initialize() {
	pros::lcd::initialize();

    drivetrain.getIMU().reset();
    while (drivetrain.getIMU().is_calibrating()) {
        pros::delay(10);
    }

    chassis.calibrate();
    chassis.setPose(0, 0, 0);
}

void disabled() {}


void competition_initialize() {}


void autonomous() {
	chassis.setPose(0, 0, 0);

    //chassis.moveToPoint(24, 0, 2000);
    chassis.turnToHeading(90, 1000, {.maxSpeed = 40});
    //chassis.moveToPoint(24, 24, 2000);
	
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