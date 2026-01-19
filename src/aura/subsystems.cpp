#include "aura/subsystems.hpp"
//#include "aura/utils.hpp"
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
*       - Park
*
*/

namespace subsystems {
    //intake class
        //constructor
        intake::intake(int intake_top_1_port, 
                    int redir_port, 
                    int intake_bottom_1_port, 
                    int intake_bottom_2_port, 
                    char hood_solanoid_port,
                    char intake_solanoid_port
                )
            :   intake_top_1(pros::Motor(intake_top_1_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                redir(pros::Motor( redir_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_bottom_1(pros::Motor(intake_bottom_1_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_bottom_2(pros::Motor(intake_bottom_2_port, pros::v5::MotorGearset::blue, pros::v5::MotorEncoderUnits::degrees)),
                intake_hood((pros::adi::Pneumatics(hood_solanoid_port, false, false))),
                intake_solanoid((pros::adi::Pneumatics(intake_solanoid_port, false, false)))
            {


            }
        //rest of the intakes functions

        void intake::setIntakeState(double lower_voltage,double redir_voltage, double upper_voltage, bool hood_solanoid_state, bool intake_solanoid_state){
            //set the intakes motors to go the ways they need to
            intake_top_1.move_voltage(floor(upper_voltage));
            redir.move_voltage(floor(redir_voltage));
            intake_bottom_1.move_voltage(floor(lower_voltage));
            intake_bottom_2.move_voltage(floor(lower_voltage));


            //set the positions of the pistons
            intake_hood.set_value(hood_solanoid_state);
            intake_solanoid.set_value(intake_solanoid_state); //uses two pistons
        }

        // void intake::driverFunctions(){
        //     //open or close the hood
        //     hood_press_count += Controller.get_digital_new_press(DIGITAL_Y);

        //     //lift or drop the intake
        //     intake_press_count += Controller.get_digital_new_press(DIGITAL_B);

        //     //Intake Control
        //     double lower_voltage = 0;
        //     double upper_voltage = 0;
        //     double redir_voltage = 0;

        //     //all the directions the intake needs to spin not currently sure what its gonna be
        //     //this is where we can control how the intake will control where it keeps the balls
        //     //Intakeing from front to top
        //     if(Controller.get_digital(DIGITAL_R1))
        //     {
        //         lower_voltage = 12000;
        //         //make it so redirspins the same way as top
        //         redir_voltage = 12000;
        //         upper_voltage = 12000;
        //     }
        //     //outake from front
        //     else if(Controller.get_digital(DIGITAL_R2))
        //     {
        //         lower_voltage = -12000;
        //         //redir spins the same way as upper
        //         redir_voltage = -12000;
        //         upper_voltage = -12000;
        //     }
        //     //scoring mid
        //     else if(Controller.get_digital(DIGITAL_L1))
        //     {   
        //         //lower spins up
        //         lower_voltage = 12000;
        //         //redir and up spins down
        //         redir_voltage = -12000;
        //         upper_voltage = 12000;
        //     }


        //     setIntakeState(lower_voltage, redir_voltage, upper_voltage, hood_press_count % 2 != 0, intake_press_count % 2 != 0);
        // }

        //alternate intake driver functions:
        //allow for hood to open and close along with diffrent scoreing modes
        //allows for easier switching between modes of what needs to spin and what doesn't
        //intake is able to keep spinning on a toggle (also closes hood)
        //intake score up button opens the hood and spins so it scores up
        //intake mid reverses the mid roller while the rest still go up
        //intake bottom button outakes out the bottom and then also stops the toggle

        void intake::driverFunctions() {
            //toggles
            //start indexing
            if (Controller.get_digital_new_press(DIGITAL_B)) {
                indexingEnabled = !indexingEnabled;
            }

            //make the mid goal scorer spin at full speed
            if (Controller.get_digital_new_press(DIGITAL_RIGHT)) {
                midFast = !midFast;
                
                //print to the controller
                Controller.clear_line(0);
                Controller.set_text(
                    0,
                    0,
                    midFast ? "FAST" : ""
                );
            }

            //open the hood on its own
            if (Controller.get_digital_new_press(DIGITAL_Y)) {
                hood_press_count++;
            }

            bool hoodState = hood_press_count % 2 != 0;
            bool intakeLiftState = false;

            //----------------------------------------------------
            //DETERMINE CURRENT MODE
            //----------------------------------------------------
            if (Controller.get_digital(DIGITAL_R1))
                currentMode = SCORE_TALL;
            else if (Controller.get_digital(DIGITAL_R2))
                currentMode = SCORE_MID;
            else if (Controller.get_digital(DIGITAL_L2))
                currentMode = OUTTAKE_LOW;
            else if (indexingEnabled)
                currentMode = INTAKE_INDEX;
            else
                currentMode = IDLE;

            double lower_voltage = 0;
            double upper_voltage = 0;
            double redir_voltage = 0;

            //----------------------------------------------------
            //APPLY MODE LOGIC FROM BUTTON PRESS
            //----------------------------------------------------
            switch(currentMode)
            {
                case INTAKE_INDEX:   // Toggle B
                    hoodState = false;          // hood closed
                    intakeLiftState = false;    // intake down
                    lower_voltage = 12000;
                    redir_voltage = 12000;
                    upper_voltage = 12000;
                    break;

                case OUTTAKE_LOW:   // L2
                    hoodState = false;
                    intakeLiftState = true;     // intake lifted
                    lower_voltage = -12000;     // eject
                    redir_voltage = -12000;
                    upper_voltage = -12000;
                    indexingEnabled = false; 
                    break;

                case SCORE_TALL:    // R1
                    hoodState = true;           // hood OPEN
                    intakeLiftState = false;
                    lower_voltage = 12000;
                    redir_voltage = 12000;
                    upper_voltage = 12000;      // strong index
                    break;

                case SCORE_MID:     // R2
                    hoodState = false;          // hood CLOSED
                    intakeLiftState = false;
                    lower_voltage = 12000;
                    
                    //toggleable redirect speed
                    redir_voltage = midFast ? -12000 : -4000;

                    upper_voltage = 12000;
                    break;

                case IDLE:
                default:
                    //everything off
                    lower_voltage = 0;
                    redir_voltage = 0;
                    upper_voltage = 0;
                    break;
            }


            setIntakeState(lower_voltage, redir_voltage, upper_voltage,
                        hoodState, intakeLiftState);
        }

    //auto functions
    /**
        @brief keep the intake spinning and the hood closed
    */
    void intake::autoPickUP(double speed){
        setIntakeState(
            speed, 
            speed, 
            speed, 
            false, 
            false);
    }

    /** 
     @brief score in the high goals in auton spins out the ball and opens the hood
    */
    void intake::autoScoreHigh(double speed){
        setIntakeState(
            speed, 
            speed, 
            speed, 
            true, //hood open
            false);

    }

    /**
        @brief redirect blocks out of the mid roller and score the mid
    */
    void intake::autoScoreMid(double speed){
        setIntakeState(
            -speed, //go down
            -speed, //goes the other direction
            speed, 
            false, 
            false);
    }

    /**
        @brief score out of the lower goal
        the lower intake needs to like spin slower?
    */
    void intake::autoScoreLow(double speed){
        setIntakeState(
            -speed, //goes the other direction
            -speed, //goes the other direction
            -speed, //goes the other direction
            false, 
            true); //lift up intake
    }

    /**
        @brief stop from spinning 
    */
    void intake::stopAuto(){
        setIntakeState(
            0, 
            0, 
            0,
            false, 
            false);
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
            //hold L1 to extend
            //release to retract
            bool buttonHeld = Controller.get_digital(DIGITAL_L1);
            setState(buttonHeld);
        }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

    //park class
        park::park(char park_solanoid_port )
        :   park_solanoid(pros::adi::Pneumatics (park_solanoid_port, false))
        {}


        void park::setState(bool state)
        {
            park_solanoid.set_value(!state);
        }

        void park::driverFunctions()
        {
            press_count += Controller.get_digital_new_press(DIGITAL_X);
            setState(press_count % 2 != 0);
        }

    
}