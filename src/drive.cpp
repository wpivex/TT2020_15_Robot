#include "Drive.hpp"
#include "SheBelieved.hpp"

Drive::Drive()
{
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

    // save ports in a vector
    leftMotorPorts.reserve(3);
    leftMotorPorts.push_back(DRIVE_LEFT_FRONT);
    leftMotorPorts.push_back(DRIVE_LEFT_MID);
    leftMotorPorts.push_back(DRIVE_LEFT_BACK);
    rightMotorPorts.reserve(3);
    rightMotorPorts.push_back(DRIVE_RIGHT_FRONT);
    rightMotorPorts.push_back(DRIVE_RIGHT_MID);
    rightMotorPorts.push_back(DRIVE_RIGHT_BACK);

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
    double forward = joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
    double turn = joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
    // this->chassis->getModel()->arcade(forward, turn);

    forward = std::clamp(forward, -1.0, 1.0);
    turn = std::clamp(turn, -1.0, 1.0);
    double leftOutput = 0;
    double rightOutput = 0;
    double max = std::copysign(std::max(std::abs(forward), std::abs(turn)), forward);
    double MAX_VELOCITY = 200;
    double MAX_VOLTAGE = 12000;

    if(forward >= 0.0) {
        if(turn >= 0.0) {
            leftOutput = max;
            rightOutput = forward - turn;
        } else {
            leftOutput = forward + turn;
            rightOutput = max;
        }
    } else {
        if(turn >= 0.0) {
            leftOutput = forward + turn;
            rightOutput = max;
        } else {
            leftOutput = max;
            rightOutput = forward - turn;
        }
    }

    leftOutput = std::clamp(leftOutput, -1.0, 1.0);
    rightOutput = std::clamp(rightOutput, -1.0, 1.0);
    // leftMotors->moveVoltage((forward + turn) * MAX_VOLTAGE);
    // rightMotors->moveVoltage((forward - turn) * MAX_VOLTAGE);
    // leftMotors->moveVoltage(leftOutput * MAX_VOLTAGE);
    // rightMotors->moveVoltage(rightOutput * MAX_VOLTAGE);
    this->moveLeft(leftOutput * 127);
    this->moveRight(rightOutput * 127);
}

void Drive::moveLeft(int power) {
    for (int port : leftMotorPorts) {
        pros::c::motor_move(port, power);
    }
}

void Drive::moveRight(int power) {
    for (int port : rightMotorPorts) {
        pros::c::motor_move(port, power);
    }
}
