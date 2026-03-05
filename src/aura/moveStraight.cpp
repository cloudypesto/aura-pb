#include "moveStraight.hpp"
#include <cmath>
#include <math.h>



extern lemlib::Chassis chassis;


void moveStraight(double distance, int timeout, float maxSpeed) {

    //get the current position
    lemlib::Pose pose = chassis.getPose();

    //convert to rad
    double thetaRad = pose.theta * M_PI / 180.0;

    //find where the robot needs to go
    double targetX = pose.x + distance * cos(thetaRad);
    double targetY = pose.y + distance * sin(thetaRad);

    chassis.moveToPose(targetX, targetY, pose.theta, timeout, {.maxSpeed = maxSpeed});
}