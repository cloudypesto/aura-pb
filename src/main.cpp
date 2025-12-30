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

    //drivetrain.getIMU().reset();
	chassis.calibrate();
    chassis.setPose(0, 0, 0);

	//forces you to wait for the drive imu to be calabrated before driving is possible
    while (drivetrain.getIMU().is_calibrating()) {
        pros::delay(10);
    }

    
}

void disabled() {}


void competition_initialize() {}



//auton options

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Linear

//moveToPoint
//takes in x cord in inches, 
//y cord in inches, 
//time out how long the robot has to be able to try to move there in millseconds,
//extra prams {} like move backwards in this example use . to find what they are
//if it should do this all async go to next point or wait so like if it reachs early flalse means it will always wait the time true means it will go as soon as it reaches the point
//chassis.moveToPoint(10, 7, 1000,{.forwards = false, .maxSpeed = 80},false );

//moveToPose
//like moveToPoint but also takes a headding theata
//this is the angle the robot will end up in after it has reached is destination
//chassis.moveToPose(10, 7, 60, 1000);


//////////////////////////////////////////////////////////////////////////////////
//Angular


//turnToHeading
//takes in headding theata
//robot will turn to the target heading on the spot
//the timeout
//extra prams
//chassis.turnToHeading(60, 1000);

//turn to point
//same as trun to headding but takes in a target point on the field rather then a heading

//swingToHeading
//only use half the drive train
//like turn to heading but rather then doing it in place it will do it by only turning one side of the drive
//takes in the heading theata
//takes in a lemlib drive side for the locked side not allowed to move the left side
//time out
//extra prams
//chassis.swingToHeading(90, lemlib::DriveSide::LEFT, 1500, {.maxSpeed = 40});

//swing to point
//like swing to headding but takes a point


/////////////////////////////////////////////////////////////////////////////////
//Path following
//pure pursuit
//pid needs to be tuned correctly
//for if you want your robot to follow a path of dots and such
//realy good for long paths that are fluid and dynamic
//to generate the path go to https://path.jerryio.com/
//this website has the game and then you can set points you want to go to on the field
//this allows you to create a path from where ever you want to start to where ever you want to go and have like extra points in the middle
//download it as a text file
//put the downloaded file into the static folder in the project
//change the ASSET() under competion_initialize to the file that we have
//actually run the pure pursuit


//follow
//takes in the path that it was given and you have set from the above instructions
//how far ahead the robot will look ahead to compute the path in inches
//time out how long is it allowed to run
//all the extra prams same as the others
//chassis.follow(pathlearning_jerryio_txt, 10, 1000);


void autonomous() {
	chassis.setPose(0, 0, 0);

	chassis.turnToHeading(90, 1000, {.maxSpeed = 40});
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

        double heading = chassis.getPose().theta;

        pros::lcd::set_text(1, "Heading: " + std::to_string(heading));


	pros::delay(10);
	}
}