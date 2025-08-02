#include "main.h"

subsystems::drivetrain drivetrain = subsystems::drivetrain
    (   9,8,10,7,3,4,2,1,'A','B','C','D', 
		5,6
    );
void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while(true){
		drivetrain.driverFunctions();
	pros::delay(10);
	}
}
