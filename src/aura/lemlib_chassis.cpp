#include "lemlib/api.hpp"
#include "aura/subsystems.hpp"
#include "aura/globals.h"

//drivetrain created in main and refrenced here
extern subsystems::drivetrain drivetrain;


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
    450,                // RPM
    0      // chase power (start with 2)
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
lemlib::ControllerSettings linearController {
    10,   // kP
    0,    // kI
    3,   // kD
    3,    // anti-windup
    1,    // small error
    100,  // small timeout
    3,    // large error
    500,  // large timeout
    20     //
};

//Angular
lemlib::ControllerSettings angularController {
    2, // proportional gain (kP)
    0, // integral gain (kI)
    0, // derivative gain (kD)
    0, // anti windup
    1.5, // small error range, in inches
    150, // small error range timeout, in milliseconds
    6, // large error range, in inches
    500, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
};



// CHASSIS (THIS IS WHAT AUTON USES RATHER THEN THE NORMAL DRIVETRAIN)
lemlib::Chassis chassis(
    drivetrainConfig,
    linearController,
    angularController,
    sensors
);