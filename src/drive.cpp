#include "drive.hpp"
#include "hamburger.hpp"

Drive::Drive() {
    MotorGroup left({
					 Motor(DRIVE_LEFT_FRONT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_MID, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_BACK, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	MotorGroup right({
					  Motor(DRIVE_RIGHT_FRONT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_MID, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_BACK, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
    leftMotors = std::make_shared<MotorGroup>(left);
    rightMotors = std::make_shared<MotorGroup>(right);
    leftMotors->setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotors->setBrakeMode(AbstractMotor::brakeMode::coast);

    // ADIEncoder leftEncoder = ADIEncoder(ENCODER_LEFT_DRIVE_TOP, ENCODER_LEFT_DRIVE_BOT, false);
    // ADIEncoder rightEncoder = ADIEncoder(ENCODER_RIGHT_DRIVE_TOP, ENCODER_RIGHT_DRIVE_BOT, true);

    chassis = ChassisControllerBuilder()
                .withMotors(leftMotors, rightMotors)
                .withGearset(AbstractMotor::gearset::green)
                .withDimensions({{3.25_in, 10.3_in},imev5GreenTPR*3/5})
                .withGains(
                    // {0.0015, 0, 0.000005}, // Distance controller gains
                    {0.0015, 0, 0.000005}, // Distance controller gains
                    {0.0015, 0, 0.000005}, // turn controller gains
                    {0.0005, 0, 0.00000}  // angle controller gains (helps drive straight)
                )
                // .withSensors(leftEncoder, rightEncoder)
                .withOdometry(StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps)
                .buildOdometry();
}

void Drive::opControlDrive(pros::Controller& joystick) {
    double forward = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127;
    double turn = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127;
    // Double stick
    this->chassis->model().arcade(forward,turn);
    // single stick
    // this->chassis->model().arcade(forward2, turn);
    // Tank
    // this->chassis->model().tank(forward, forward2);
}
