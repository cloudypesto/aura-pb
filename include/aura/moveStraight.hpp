#pragma once

#include "lemlib/api.hpp"

/**
    @brief  Moves the robot straight forward or backward relative to its current heading
    Calculates a new target position based on the robots current pose from LemLibs Odometry

    if your pid is like bad it will not go in a stright like :3

    @param distance Distance in inches to move.
                    Positive = forward
                    Negative = backward
    @param timeout  Maximum time in milliseconds the robot will attempt
                    to reach the target before stopping (default 2000ms)
    @param speed The speed the robot will attempt to do the move (default 50)

    This movement is relative to the robot rather then feild relitive like the other LemLib functions

    Usage:
    moveStraight(24, 3000, 100); //move 24 inchs, with a timeout of 3 seconds, with a speed of 100
    moveStright(24); ///move 24 inchs, with a timeout of 2 seconds, with a speed of 50

 */
void moveStraight(double distance, int timeout = 2000, float maxSpeed = 50);