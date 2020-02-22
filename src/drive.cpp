#include "Drive.hpp"
#include "SheBelieved.hpp"

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

    leftEncoder = std::make_shared<ADIEncoder>(ENCODER_LEFT_DRIVE_TOP, ENCODER_LEFT_DRIVE_BOT, true);
    rightEncoder = std::make_shared<ADIEncoder>(ENCODER_RIGHT_DRIVE_TOP, ENCODER_RIGHT_DRIVE_BOT, false);

    std::shared_ptr<okapi::OdomChassisController> c = ChassisControllerBuilder()
                .withMotors(leftMotors, rightMotors)
                .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 4.5_in},1024})
                .withGains(
                    {0.0015, 0, 0.00005}, // Distance controller gains
                    {0.006, 0, 0.0005}, // turn controller gains
                    {0.0005, 0, 0.00000}  // angle controller gains (helps drive straight)
                )
                .withSensors(leftEncoder, rightEncoder)
                .withClosedLoopControllerTimeUtil(50, 5, 100_ms)
                .withOdometry({{3.25_in, 4.5_in},1024}, StateMode::CARTESIAN, 0_mm, 0_deg)
                .buildOdometry();
    chassis = std::dynamic_pointer_cast<okapi::DefaultOdomChassisController>(c);
    chassisPID = std::dynamic_pointer_cast<okapi::ChassisControllerPID>(chassis->getChassisController());    
}

void Drive::opControl(pros::Controller& joystick) {
    double forward = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    double turn = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    forward = abs(forward) - 10 <=0 ? 0 : forward;
    turn = abs(turn) - 10 <=0 ? 0 : turn;
    this->chassis->model().arcade(forward / 127,turn / 127);
}
