#include "lemlib/api.hpp"
#include "aura/subsystems.hpp"
#include "aura/globals.h"

//drivetrain created in main and refrenced here
extern subsystems::drivetrain drivetrain;


//set up the tracking wheels
lemlib::TrackingWheel verticalWheel(
    &drivetrain.getYTrackingEncoder(),
    lemlib::Omniwheel::NEW_2,
    0.0
);

lemlib::TrackingWheel horizontalWheel(
    &drivetrain.getXTrackingEncoder(),
    lemlib::Omniwheel::NEW_2,
    0.0
);

//apply our drive train to lemlib
lemlib::Drivetrain drivetrainConfig {
    &drivetrain.getLeftDrive(),
    &drivetrain.getRightDrive(),
    11.5,        // track width (in)
    3.25,     // wheel diameter (in)
    450,                // RPM
    2       // chase power (start with 2)
};


//set up the odom sensors we currently have
lemlib::OdomSensors sensors {
    &verticalWheel,
    nullptr,                //second vertical wheel (unused)
    &horizontalWheel,
    nullptr,              //second horizontal wheel (unused)
    &drivetrain.getIMU()          //IMU
};

//PID controllers
//Linear
lemlib::ControllerSettings linearController {
    10,   // kP
    0,    // kI
    30,   // kD
    3,    // anti-windup
    1,    // small error
    100,  // small timeout
    3,    // large error
    500,  // large timeout
    0     // slew (0 = disabled)
};

//Angular
lemlib::ControllerSettings angularController {
    8,
    0,
    45,
    3,
    1,
    100,
    3,
    500,
    0
};



// CHASSIS (THIS IS WHAT AUTON USES RATHER THEN THE NORMAL DRIVETRAIN)
lemlib::Chassis chassis(
    drivetrainConfig,
    linearController,
    angularController,
    sensors
);