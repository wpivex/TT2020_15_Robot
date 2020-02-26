#include "lift.hpp"
#include "SheBelieved.hpp"


Lift::Lift() {
    MotorGroup motors({Motor(ARM_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
                        Motor(ARM_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
    armMotors = std::make_shared<MotorGroup>(motors);
	  armMotors->setBrakeMode(AbstractMotor::brakeMode::hold);
}

void Lift::setLiftPower(int velocity) {
    armMotors->moveVelocity(velocity);
}

void Lift::opControl(pros::Controller& joystick) {
    double up = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127 * 100;
    setLiftPower(up);
}

void Lift::moveToPos(int pos, int speed) {
    armMotors->moveAbsolute(pos, speed);
}
