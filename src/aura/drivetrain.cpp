#include "aura/subsystems.hpp"
#include "aura/utils.hpp"
#include "globals.h"
#include <cmath>

// file containing all of the drive train based functions

namespace subsystems
{
    drivetrain::drivetrain(int left_1_port, int left_2_port, int left_3_port, int left_4_port,
                           int right_1_port, int right_2_port, int right_3_port, int right_4_port,
                           char x_tracking_encoder_top, char x_tracking_encoder_bottom,
                           char y_tracking_encoder_top, char y_tracking_encoder_bottom,
                           int imu_1_port)
        : left_1(pros::Motor(left_1_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          left_2(pros::Motor(left_2_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          left_3(pros::Motor(left_3_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          left_4(pros::Motor(left_4_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),

          right_1(pros::Motor(right_1_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          right_2(pros::Motor(right_2_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          right_3(pros::Motor(right_3_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          right_4(pros::Motor(right_4_port, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees)),
          XTrackingEncoder(pros::adi::Encoder(x_tracking_encoder_top, x_tracking_encoder_bottom)),
          YTrackingEncoder(pros::adi::Encoder(y_tracking_encoder_top, y_tracking_encoder_bottom)),
          imu_1(pros::Imu(imu_1_port))
    {
        // adds the rest of the motors to the group
        leftDrive.append(left_2);
        leftDrive.append(left_3);
        leftDrive.append(left_4);

        rightDrive.append(right_2);
        rightDrive.append(right_3);
        rightDrive.append(right_4);
    }

    void drivetrain::driverFunctions()
    {
        // just like change out to your perfered control system

        // arcade drive code
        int y = Controller.get_analog(ANALOG_LEFT_Y);
        int x = Controller.get_analog(ANALOG_RIGHT_X);

        int y_output = linearToCubed(y, 127, 1);
        int x_output = linearToCubed(x, 127, 1);

        int left_voltage = pctToVoltage(y_output + x_output);
        int right_voltage = pctToVoltage(y_output - x_output);

        this->setDriveVoltage(left_voltage, right_voltage);

        // single stick left
        //  int y = Controller.get_analog(ANALOG_LEFT_Y);
        //  int x = Controller.get_analog(ANALOG_LEFT_X);

        // int y_output = linearToCubed(y, 127, 1);
        // int x_output = linearToCubed(x, 127, 1);

        // int left_voltage  = pctToVoltage(y_output - x_output);
        // int right_voltage = pctToVoltage(y_output + x_output);

        // this->setDriveVoltage(left_voltage, right_voltage);

        // tank drive code
        //  int left_input = Controller.get_analog(ANALOG_RIGHT_Y);
        //  int right_input = Controller.get_analog(ANALOG_LEFT_Y);

        // int left_output = linearToCubed(left_input, 127, 1);
        // int right_output = linearToCubed(right_input, 127, 1);

        // int left_voltage = pctToVoltage(left_output);
        // int right_voltage = pctToVoltage(right_output);

        // this->setDriveVoltage(left_voltage, right_voltage);
    }

    void drivetrain::setDriveVoltage(double left_voltage, double right_voltage)
    {

        // convert to ints
        int left_voltage_int = floor(left_voltage);
        int right_voltage_int = floor(right_voltage);

        leftDrive.move_voltage(left_voltage_int);
        rightDrive.move_voltage(right_voltage_int);
    }

    void drivetrain::setBrakeMode(pros::motor_brake_mode_e brake_mode)
    {
        leftDrive.set_brake_mode(brake_mode);
        rightDrive.set_brake_mode(brake_mode);
    }

    // auton just allow it to go straint lol

    void subsystems::drivetrain::moveDistance(double inches, double speed, int timeout)
    {
        // reset motor encoders
        leftDrive.tare_position();
        rightDrive.tare_position();

        // calculate target encoder position in degrees
        double wheelCircumference = M_PI * DRIVE_WHEEL_DIAMETER;
        double rotations = inches / wheelCircumference;
        double targetDegrees = rotations * 360.0;

        // PID constants
        double kP = 9.0; // Proportional gain
        double kI = 0;   // Integral gain (start small)
        double kD = 100; // Derivative gain

        // convert speed percentage to max voltage limit
        double maxVoltage = (fabs(speed) / 100.0) * 12000.0;
        double minVoltage = 1500; // Minimum to overcome friction

        // PID variables
        double integral = 0;
        double lastError = 0;

        // track start time for timeout
        uint32_t startTime = pros::millis();

        // movement loop
        while (pros::millis() - startTime < timeout)
        {
            // get average position of both sides (keep sign for direction)
            double avgPosition = (leftDrive.get_position() + rightDrive.get_position()) / 2.0;

            // calculate error (keeps direction)
            double error = targetDegrees - avgPosition;

            // check if reached the target (within tolerance)
            if (fabs(error) < 5)
            {
                break;
            }

            // calculate integral (accumulated error)
            integral += error;

            // anti windup: prevent integral from getting too large
            double maxIntegral = 3000;
            if (integral > maxIntegral)
                integral = maxIntegral;
            if (integral < -maxIntegral)
                integral = -maxIntegral;

            // calculate derivative (rate of change of error)
            double derivative = error - lastError;

            // calculate PID output
            double pidOutput = (kP * error) + (kI * integral) + (kD * derivative);

            // clamp voltage to max speed
            double voltage = pidOutput;
            if (voltage > maxVoltage)
                voltage = maxVoltage;
            if (voltage < -maxVoltage)
                voltage = -maxVoltage;

            // apply minimum voltage to overcome static friction
            if (fabs(voltage) < minVoltage && fabs(error) > 5)
            {
                voltage = (voltage > 0) ? minVoltage : -minVoltage;
            }

            // apply voltage to motors
            setDriveVoltage(voltage, voltage);

            // update last error for next iteration
            lastError = error;

            pros::delay(10);
        }

        // stop the robot
        setDriveVoltage(0, 0);
    }

} // namespace subsystems