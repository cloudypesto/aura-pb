#include <aura/subsystems.hpp>

namespace subsystems {
    drivetrain::drivetrain(int left_1_port, int left_2_port, int left_3_port, int left_4_port,
                           int right_1_port, int right_2_port, int right_3_port, int right_4_port,
                           char x_tracking_encoder_top, char x_tracking_encoder_bottom,
                           char y_tracking_encoder_top, char y_tracking_encoder_bottom,
                           int imu_1_port, int imu_2_port)
        : 
            left_1(pros::Motor(-left_1_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            left_2(pros::Motor(left_2_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            left_3(pros::Motor(-left_3_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            left_4(pros::Motor(left_4_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            
            right_1(pros::Motor(right_1_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            right_2(pros::Motor(-right_2_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            right_3(pros::Motor(right_3_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            right_4(pros::Motor(-right_4_port, pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees)),
            XTrackingEncoder(pros::ADIEncoder(x_tracking_encoder_top, x_tracking_encoder_bottom)),
            YTrackingEncoder(pros::ADIEncoder(y_tracking_encoder_top, y_tracking_encoder_bottom)),
            imu_1(pros::Imu(imu_1_port)),
            imu_2(pros::Imu(imu_2_port))
        {
            leftDrive.append(left_2);
            leftDrive.append(left_3);
            leftDrive.append(left_4);

            rightDrive.append(right_2);
            rightDrive.append(right_3);
            rightDrive.append(right_4);
        }
    

    void drivetrain::driverFunctions() {
    }

    void drivetrain::setDriveVoltage(double left_voltage, double right_voltage) {
        
        //convert to ints
        int left_voltage_int = floor(left_voltage);
        int right_voltage_int = floor(right_voltage);

        leftDrive.move_voltage(left_voltage_int);
        rightDrive.move_voltage(right_voltage_int);

    }

    void drivetrain::setBrakeMode(pros::motor_brake_mode_e brake_mode) {
        leftDrive.set_brake_mode(brake_mode);
        rightDrive.set_brake_mode(brake_mode);
    }

} // namespace subsystems