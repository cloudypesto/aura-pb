#include "main.h"
#include "../include/aura/globals.h"
#include "aura/devices.hpp"
#include "aura/subsystems.hpp"

#include "aura/lemlib.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/api.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

#include "aura/autonselector.hpp"

// create the drive train

//making sure the drive is created first idk dog

subsystems::drivetrain drivetrain = subsystems::drivetrain(LEFT_MOTOR_1,
                                                           LEFT_MOTOR_2,
                                                           LEFT_MOTOR_3,
                                                           LEFT_MOTOR_4,
                                                           RIGHT_MOTOR_1,
                                                           RIGHT_MOTOR_2,
                                                           RIGHT_MOTOR_3,
                                                           RIGHT_MOTOR_4,
                                                           'X',
                                                           'X',
                                                           'X',
                                                           'X',
                                                           IMU1);




//creating lemlib stuff to fix hopefully
//set up the tracking wheels
lemlib::TrackingWheel verticalWheel(
    &drivetrain.getYTrackingEncoder(),
    TRACKING_WHEEL_DIAMETER,
    VERTICAL_OFFSET
);
lemlib::TrackingWheel horizontalWheel(
    &drivetrain.getXTrackingEncoder(),
    TRACKING_WHEEL_DIAMETER, 
    HORIZONTAL_OFFSET
);

//apply our drive train to lemlib
lemlib::Drivetrain drivetrainConfig {
    &drivetrain.getLeftDrive(),
    &drivetrain.getRightDrive(),
    TRACKWIDTH,        
    DRIVE_WHEEL_DIAMETER,
    600,                
    8 //horizontalDrift is 2
    //traction wheels horizontalDrift would be 8
};


//set up the odom sensors we currently have
//on the bot i have rn we have no odom pods so setting them to null pointer


lemlib::OdomSensors sensors {
    // &verticalWheel,
    // nullptr,                //second vertical wheel
    // &horizontalWheel,
    // nullptr,              //second horizontal wheel
    // &drivetrain.getIMU()  

    //set to null pointer untill the odom is actually added
    nullptr,
    nullptr,               
    nullptr,
    nullptr,              
    &drivetrain.getIMU()          //IMU
};

//PID controllers
//Linear
lemlib::ControllerSettings linearController{
    8,  // kP
    0,   // kI
    8,   // kD
    0,   // anti-windup
    1,   // small error
    90, // small timeout
    5,   // large error
    100, // large timeout
    20   //
};

// Angular
lemlib::ControllerSettings angularController{
    2.2,  // proportional gain (kP)
    0,  // integral gain (kI)
    15, // derivative gain (kD)
    0,  // anti windup
    1,  // small error range, in inches
    90,  // small error range timeout, in milliseconds
    3,  // large error range, in inches
    500,  // large error range timeout, in milliseconds
    0   // maximum acceleration (slew)
};



// CHASSIS (THIS IS WHAT AUTON USES RATHER THEN THE NORMAL DRIVETRAIN)
lemlib::Chassis chassis(
    drivetrainConfig,
    linearController,
    angularController,
    sensors
);


// create other sub systems





// set up intake
subsystems::intake intake = subsystems::intake(INTAKE_TOP_1,
                                               INTAKE_REDIR,
                                               INTAKE_BOTTOM_1,
                                               INTAKE_BOTTOM_2,
                                               HOOD,
                                               INAKE);

// set up match load
subsystems::matchload matchload = subsystems::matchload(MATCHLOAD);


void initialize()
{

    AutonColors auton_sel_colours = {
        .bg_color = lv_color_hex(0x826082),         // black
        .btn_normal = lv_color_hex(0xd692c6),       // bink
        .btn_selected = lv_color_hex(0x20c418),     // geen
        .btn_text_normal = lv_color_hex(0xffffff),  // White
        .btn_text_selected = lv_color_hex(0x000000) // Black
    };
    auton_selector_init_colors(auton_sel_colours);

    drivetrain.getIMU().reset();
    while (drivetrain.getIMU().is_calibrating()) {
    	Controller.set_text(0, 0, "IMU calibrating...");
    	//has to wait 50 to be able to change the text again
        pros::delay(50);
    }
    // get rid of text
    // pros::lcd::clear_line(4);
    pros::delay(50);
    Controller.clear_line(0);

    chassis.calibrate(true);
    chassis.setPose(0, 0, 0);
    pros::delay(100);

   
}

void disabled() {}

void competition_initialize() {}

// auton options

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Linear

// ONLY WORK WITH TRACKING WHEELS!!!!!!!!!!!!
// min we need a horrzontal

// current my linear without any special
// drive train function moveDistance
// drivetrain.moveDistance(-20, 20, 2000);
// takes a distance in inches
// takes a speed
// takes a time its allowed to do it in

// moveToPoint
// takes in x cord in inches,
// y cord in inches,
// time out how long the robot has to be able to try to move there in millseconds,
// extra prams {} like move backwards in this example use . to find what they are
// if it should do this all async go to next point or wait so like if it reachs early flalse means it will always wait the time true means it will go as soon as it reaches the point
// chassis.moveToPoint(10, 7, 1000,{.forwards = false, .maxSpeed = 80},false );

// moveToPose
// like moveToPoint but also takes a headding theata
// this is the angle the robot will end up in after it has reached is destination
// chassis.moveToPose(10, 7, 60, 1000);

// use the lead to allow the use of the boomerang controler
// chassis.moveToPose(
//      0, // x = 0
//      0, // y = 0
//      0, // theta = 0
//      4000, // timeout of 4000ms
//      {.lead = 0.3, .horizontalDrift = 8}
//  );

//////////////////////////////////////////////////////////////////////////////////
// Angular

// turnToHeading
// takes in headding theata
// robot will turn to the target heading on the spot
// the timeout
// extra prams
// chassis.turnToHeading(60, 1000);

// turn to point
// same as trun to headding but takes in a target point on the field rather then a heading

// swingToHeading
// only use half the drive train
// like turn to heading but rather then doing it in place it will do it by only turning one side of the drive
// takes in the heading theata
// takes in a lemlib drive side for the locked side not allowed to move the left side
// time out
// extra prams
// chassis.swingToHeading(90, lemlib::DriveSide::LEFT, 1500, {.maxSpeed = 40});

// swing to point
// like swing to headding but takes a point

/////////////////////////////////////////////////////////////////////////////////
// Path following
// pure pursuit
// pid needs to be tuned correctly
// for if you want your robot to follow a path of dots and such
// realy good for long paths that are fluid and dynamic
// to generate the path go to https://path.jerryio.com/
// this website has the game and then you can set points you want to go to on the field
// this allows you to create a path from where ever you want to start to where ever you want to go and have like extra points in the middle
// download it as a text file
// put the downloaded file into the static folder in the project
// change the ASSET() under competion_initialize to the file that we have
// actually run the pure pursuit

// follow
// takes in the path that it was given and you have set from the above instructions
// how far ahead the robot will look ahead to compute the path in inches
// time out how long is it allowed to run
// all the extra prams same as the others
// uses _ rather then .
// chassis.follow(pathlearning_jerryio_txt, 10, 1000);

// async – whether the function should be run asynchronously. true by default

// set the path as an asset so it can be used
ASSET(examplekillme_txt);
ASSET(hehehe_txt);

//go grab 4 and then go park
void left_high_score()
{
    chassis.setPose(-46.566, 14, 0);
    //go match load first

    chassis.moveToPose(-46, 46, 0, 2000,{.forwards = true , .maxSpeed = 90 , .minSpeed=20}, false);
    //delay to stop rocking
    pros::delay(200);
    //trun to the match loader
    chassis.turnToHeading(270, 500);

    //drive to match loader
    chassis.moveToPoint(-57, 46, 2000);

    //start intake
    intake.autoIndex();
    pros::delay(500);

    intake.stopAuto();


    //go score
    chassis.moveToPose(-30, 46, 270, 3000, {.forwards = false});
    intake.autoScoreHigh();
    pros::delay(3000);

    
    // intake.stopAuto();

    // //go to the middle tile
    // chassis.moveToPose(-46, 46, 270, 2000,{.forwards = true , .maxSpeed = 90 , .minSpeed=20}, false);

    // chassis.turnToHeading(135, 500);

    // //drive to the balls
    // intake.autoIndex();
    // chassis.moveToPose(-6.063, 38.199, 45, 2000,{.forwards = true , .horizontalDrift = 10, .lead = -7, .maxSpeed = 90 , .minSpeed=20, });





    //go try and score

    //go park



}


//this auto will go grab 4
//and then go park
void rightRushAuto()
{
    chassis.setPose(0, 0, 180);


    drivetrain.moveVelocity(100);

    pros::delay(2400);
    drivetrain.moveVelocity(0);

    chassis.turnToHeading(270, 1000);
    pros::delay(1000);





    // pros::delay(2500);
    // drivetrain.setDriveVoltage(0, 0);


    // chassis.turnToHeading(270, 1000);
    // pros::delay(1000);


    // matchload.setState(true);
    // intake.autoIndex();
    // pros::delay(500);

    // drivetrain.setDriveVoltage(100, 100);
    // pros::delay(5000);


    
    
    //move to match loader

    // chassis.moveToPose(46, -48, 180, 5000, { .forwards = true ,  .maxSpeed = 90 , .minSpeed=60}, false);
    // // chassis.waitUntilDone();
    // pros::delay(500);

    // //chassis.turnToHeading(0, 3000);

    // //turn to match loader
    // chassis.turnToHeading(270, 1000, {.maxSpeed = 40}, false);
    // chassis.waitUntilDone();

    // //put out match load and start intaking
    // matchload.setState(true);
    // intake.autoIndex();
    // pros::delay(300);

    // // //go grab blocks form loader
    // chassis.moveToPose(-60, -46, 270, 1300, {.forwards = true, .lead = 0.1, .maxSpeed = 40}, false);
    // pros::delay(500);

    // // //leave match loader and go to the goal and then score
    // chassis.moveToPose(-28, -46, 270, 2000, {.forwards = false, .maxSpeed = 95}, false);
    // matchload.setState(false);
    // chassis.waitUntilDone();
    // intake.autoScoreHigh();
    // pros::delay(1000);


    // //wait at the end of the goal for like uhhh some time 

    // pros::delay(15000);

    // // leave the goal and go park
    // chassis.moveToPose(-62.33, -17, 0, 3000, {.forwards = true, .lead = 0.1, .maxSpeed = 40});

    // chassis.moveToPoint(-62.33, 0, 1000);

}

void leftRushAuto()
{

}

void skillsAuto()
{
    intake.autoIndex();
    pros::delay(1000);
    intake.stopAuto();
}

void autonomous()
{

    //skillsAuto();
    rightRushAuto();

    // switch (auton_selector_get())
    // {
    // case Auton::LEFT_HIGH_SCORE:
    //     
    //     left_high_score();
    //     break;

    // case Auton::RIGHT_RUSH: 
    //     rightRushAuto();
    //     break;

    // case Auton::RIGHT_SCORE:
    //     leftRushAuto();
    //     break;

    // case Auton::SKILLS:
    //     skillsAuto();
    //     break;

    // default:
    //     break;
    // }
}

void opcontrol()
{
    //run auto first
    //autonomous();

    // end anything being used in auton
    drivetrain.setBrakeMode(MOTOR_BRAKE_COAST);
    //intake.stopAuto();

    //idk they just have this
    pros::delay(500);

    while (true)
    {
        // run all the driver functions and anything that needs to be constantly running
        // control drive
        drivetrain.driverFunctions();
        // control intake
        intake.driverFunctions();
        // matchloader
        matchload.driverFunctions();
        

        // run auto lol
        // if(Controller.get_digital(DIGITAL_DOWN)){
        //     autonomous();
        // }

        pros::delay(10);
    }
}