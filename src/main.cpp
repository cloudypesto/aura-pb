#include "main.h"
#include "../include/aura/globals.h"
#include "aura/devices.hpp"
#include "aura/subsystems.hpp"

#include "aura/lemlib.hpp"
#include "lemlib/asset.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

#include "aura/autonselector.hpp"

// create the drive train
subsystems::drivetrain drivetrain = subsystems::drivetrain(LEFT_MOTOR_1,
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
                                                           IMU1);

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

// set up descore
subsystems::descore descore = subsystems::descore(DESCORE);

// set up park
subsystems::park park = subsystems::park(PARK);

void initialize()
{

    AutonColors auton_sel_colours = {
        .bg_color = lv_color_hex(0x000000),         // black
        .btn_normal = lv_color_hex(0xb35ee0),       // pruble
        .btn_selected = lv_color_hex(0x20c418),     // geen
        .btn_text_normal = lv_color_hex(0xffffff),  // White
        .btn_text_selected = lv_color_hex(0x000000) // Black
    };
    auton_selector_init_colors(auton_sel_colours);

    drivetrain.getIMU().reset();
    while (drivetrain.getIMU().is_calibrating())
    {
        // pros::lcd::print(4,"IMU is calibrating drive is locked out");
        Controller.set_text(0, 0, "IMU calibrating...");
        // has to wait 50 to be able to change the text again
        pros::delay(50);
    }
    // get rid of text
    // pros::lcd::clear_line(4);
    Controller.clear_line(0);

    chassis.calibrate(true);
    chassis.setPose(0, 0, 0);

    // pros::Task screen_task([&]() {
    //     while (true) {
    //         //print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    //         //delay to save resources
    //         pros::delay(200);
    //     }
    // });
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

// Make like these to have diff autos to swap through
void testauto()
{
    chassis.setPose(63.5, -16.5, 270);
    descore.setState(false);
    intake.autoIndex();
    chassis.moveToPose(8, -42.5, 200, 5000, {.lead = 0.3, .maxSpeed = 100, .minSpeed = 20}, false);
    matchload.setState(true);
    pros::delay(300);
    matchload.setState(false);
    pros::delay(300);
    chassis.moveToPose(24, -24, 135, 3000, {.forwards = false, .maxSpeed = 95});
    chassis.moveToPose(48, -47, 90, 2000, {.lead = .1, .maxSpeed = 75});
    matchload.setState(true);
    pros::delay(700);
    chassis.moveToPose(63, -46, 90, 1000, {.maxSpeed = 95});
    pros::delay(950);
    chassis.moveToPose(26, -46, 90, 3000, {.forwards = false, .maxSpeed = 95});
    chassis.waitUntilDone();
    chassis.setPose(26, -48, 90);
    intake.autoScoreHigh();
    pros::delay(2000);
    chassis.moveToPose(62, -48, 90, 1000, {.maxSpeed = 65});
    intake.autoScoreHigh();
    pros::delay(3000);
    intake.autoIndex();
    pros::delay(3000);
    chassis.setPose(63, -48, 90);
    chassis.moveToPose(30, -30, 135, 4000, {.forwards = false, .maxSpeed = 95});
    matchload.setState(false);

    // chassis.follow(hehehe_txt, 20, 4000);
    // chassis.turnToHeading(90, 40000, {.maxSpeed = 40},false);
    // chassis.moveToPose(-36, -24, 270, 5000, {.maxSpeed = 95});
    // chassis.moveToPoint(0, 0, 4000,{ .maxSpeed = 40});
    // pros::delay(450);
    // chassis.moveToPoint(24, 0, 3000, {.maxSpeed = 40});

    // current go straight
    // drivetrain.moveDistance(10, 70, 1000);
    // pros::delay(200);

    // chassis.swingToHeading(90, lemlib::DriveSide::LEFT ,1000, {.maxSpeed = 40},true);
    // drivetrain.moveDistance(-10, 70, 1000);
    // pros::delay(200);

    // drivetrain.moveDistance(12, 20, 2000);
    // pros::delay(200);

    // intake.autoIndex();

    // intake.autoScoreHigh();
    // intake.autoScoreMid();
    // intake.autoScoreLow();

    // descore.setState(true);
    // pros::delay(2000);

    // descore.setState(false);

    // matchload.setState(true);
    // pros::delay(2000);

    // matchload.setState(false);
    // pros::delay(2000);
}

void RushAuto()
{
    chassis.setPose(-63.5, -16.5, 90);
    intake.autoIndex();

    // ball rush
    chassis.moveToPose(-7.5, -42.5, 150, 5000, {.lead = 0.4, .minSpeed = 45}, false);
    chassis.waitUntilDone();
    pros::delay(500);

    // back up to -48,-48 facing 45
    chassis.moveToPose(-48, -56, 45, 4000, {.forwards = false, .lead = 0.6, .maxSpeed = 95,.minSpeed=30}, false);
    intake.stopAuto();
    // chassis.waitUntil(10);
    // matchload.setState(true);
    // chassis.waitUntilDone();


    pros::delay(500);
    chassis.turnToHeading(270, 1000, {}, false);
    matchload.setState(true);
    pros::delay(500);

    intake.autoIndex();
    chassis.moveToPose(-67, -56.5,270, 1000, {.maxSpeed = 50, .minSpeed = 40}, false);
    chassis.waitUntilDone();
    pros::delay(900); // wait to match load
    intake.stopAuto();


    chassis.moveToPose(-28, -57, 270,1000, {.forwards = false, .maxSpeed = 95}, false);
    chassis.waitUntilDone();
    intake.autoScoreHigh();
    chassis.setPose(-28,-48,270);
    pros::delay(2500);
    
    chassis.moveToPoint(-67, -48,1000, {.maxSpeed = 50, .minSpeed = 40}, false);
    intake.autoIndex();
    pros::delay(1400);

    intake.stopAuto();
    chassis.moveToPose(-24,-24, 225,3000, {.forwards = false,  .maxSpeed = 95}, false);
    matchload.setState(false);
    chassis.waitUntilDone();
    pros::delay(500);


    

}

void WingAuto()
{
    chassis.setPose(-50, 8, 0);
    chassis.moveToPose(-48,48,0,5000,{.forwards = true,.maxSpeed = 90,.minSpeed=20},false);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.turnToHeading(270,1000,{.maxSpeed = 30},false);
    chassis.waitUntilDone();
    matchload.setState(true);
    intake.autoIndex();
    pros::delay(300);
    chassis.moveToPose(-65,50,270,1300,{.forwards=true,.lead=0.1,.maxSpeed=40},false);
    chassis.moveToPose(-28,50,270,2000,{.forwards=false,.maxSpeed=95},false);
    matchload.setState(false);
    chassis.waitUntilDone();
    intake.autoScoreHigh();
    pros::delay(1000);
    chassis.swingToHeading(90,lemlib::DriveSide::RIGHT,2000,{.maxSpeed=60},false);
    pros::delay(100);
    chassis.turnToHeading(255,1000,{.direction=lemlib::AngularDirection::CCW_COUNTERCLOCKWISE,.maxSpeed=90},false);
    intake.stopAuto();
    chassis.moveToPose(-12,58.5,270,3000,{.forwards=false,.maxSpeed=95},false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(1000);



    
}

void skillsAuto()
{
    chassis.setPose(0, 0, 0);
    chassis.follow(hehehe_txt, 15, 6000);
}

void autonomous()
{
    RushAuto();
    // WingAuto();
    // switch (auton_selector_get())
    // {
    // case Auton::TEST:
    //     testauto();
    //     break;

    // case Auton::LEFT_RUSH:
    //     RushAuto();
    //     break;

    // case Auton::RIGHT_RUSH:
    //     rightRushAuto();
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
    autonomous();
    // // end anything being used in auton
    drivetrain.setBrakeMode(MOTOR_BRAKE_COAST);
    // intake.stopAuto();
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
        // descore
        descore.driverFunctions();
        // park
        park.driverFunctions();

        pros::delay(10);
    }
}