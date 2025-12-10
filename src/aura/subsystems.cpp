#include "aura/subsystems.hpp"
#include "aura/utils.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"

/**
*   Contains all the non DriveTrain functions 
*   for any other systems on the robot
*
*   Contains:
*       - Intake (has the hood and the intake shifter)
*       - Match Load
*       - Descore
*
*/

namespace subsystems {
    //intake class
        //constructor
        intake::intake(int intake_top_1_port, 
                    int intake_top_2_port, 
                    int intake_bottom_1_port, 
                    int intake_bottom_2_port, 
                    char hood_solanoid_port,
                    char intake_solanoid_1_port,
                    char intake_solanoid_2_port
                )
            :   intake_top_1(pros::Motor(intake_top_1_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_top_2(pros::Motor(intake_top_2_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_bottom_1(pros::Motor(intake_bottom_1_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_bottom_2(pros::Motor(intake_bottom_2_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_hood((pros::adi::Pneumatics(hood_solanoid_port, false, false))),
                intake_piston_1((pros::adi::Pneumatics(intake_solanoid_1_port, false, false))),
                intake_piston_2((pros::adi::Pneumatics(intake_solanoid_2_port, false, false)))
            {


            }
        //rest of the intakes functions

        void intake::setIntakeState(double lower_voltage, double upper_voltage, bool hood_solanoid_state, bool intake_solanoid_state){
            //set the intakes motors to go the ways they need to
            intake_top_1.move_voltage(floor(upper_voltage));
            intake_top_2.move_voltage(floor(upper_voltage));
            intake_bottom_1.move_voltage(floor(lower_voltage));
            intake_bottom_1.move_voltage(floor(lower_voltage));


            //set the positions of the pistons
            intake_hood.set_value(hood_solanoid_state);
            intake_piston_1.set_value(intake_solanoid_state);
            intake_piston_2.set_value(intake_solanoid_state);
        }

        void intake::driverFunctions(){
            //open or close the hood
            hood_press_count += Controller.get_digital_new_press(DIGITAL_Y);

            //lift or drop the intake
            intake_press_count += Controller.get_digital_new_press(DIGITAL_B);

            //Intake Control
            double lower_voltage = 0;
            double upper_voltage = 0;

            //all the directions the intake needs to spin not currently sure what its gonna be
            //this is where we can control how the intake will control where it keeps the balls
            //Intakeing from front to top
            if(Controller.get_digital(DIGITAL_R1))
            {
                lower_voltage = 12000;
                upper_voltage = 12000;
            }
            //outake from front
            else if(Controller.get_digital(DIGITAL_R2))
            {
                lower_voltage = -12000;
                upper_voltage = -12000;
            }
            //scoring mid
            else if(Controller.get_digital(DIGITAL_L1))
            {   
                lower_voltage = 12000;
                upper_voltage = -12000;
            }


            setIntakeState(lower_voltage, upper_voltage, hood_press_count % 2 != 0, intake_press_count % 2 != 0);
        }

        
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    //matchload class
        //constructor
        matchload::matchload(char matchload_solanoid_port) 
        :   matchload_solanoid(pros::adi::Pneumatics (matchload_solanoid_port, false))
        {}

        void matchload::setState(bool matchloadState)
        {
            matchload_solanoid.set_value(matchloadState);
        }

        void matchload::driverFunctions()
        {
            matchload_press_count += Controller.get_digital_new_press(DIGITAL_RIGHT);

            //pressed odd amount of times
            if(matchload_press_count % 2 != 0)
            {
                setState(1);
            }
            else
            {
                setState(0);
            }  
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    //descorer class
    //Constructor
        descore::descore(char descore_solanoid_port) 
        :   descore_solanoid(pros::adi::Pneumatics (descore_solanoid_port, false))
        {}

        void descore::setState(bool state)
        {
            descore_solanoid.set_value(!state);
        }

        void descore::driverFunctions()
        {
            pressCount += Controller.get_digital_new_press(DIGITAL_A);
            setState(pressCount % 2 != 0);
        }
    
}