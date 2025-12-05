//file to contain non drivetrain functions
#include "aura/subsystems.hpp"
#include "aura/utils.hpp"
#include "pros/motors.hpp"

namespace subsystems {
    //intake class
        //constructor
        intake::intake(int intake_top_1_port, 
                    int intake_top_2_port, 
                    int intake_bottom_1_port, 
                    int intake_bottom_2_port, 
                    char hood_solanoid_port)
            :   intake_top_1(pros::Motor(intake_top_1_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_top_2(pros::Motor(intake_top_2_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_bottom_1(pros::Motor(intake_bottom_1_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_bottom_2(pros::Motor(intake_bottom_2_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_hood((pros::adi::Pneumatics(hood_solanoid_port, false, false)))

            {


            }
        //rest of the intakes functions

        
    
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