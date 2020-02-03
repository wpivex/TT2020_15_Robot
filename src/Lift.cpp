#include "lift.hpp"
#include "SheBelieved.hpp"


Lift::Lift() {
    MotorGroup motors({Motor(FOURBAR_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
                        Motor(FOURBAR_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
    armMotors = std::make_shared<MotorGroup>(motors);
	armMotors->setBrakeMode(AbstractMotor::brakeMode::hold);
}

void Lift::setLiftPower(int velocity) {
    armMotors->moveVelocity(velocity);
}

void Lift::opControl(pros::Controller& joystick) {
    double up = (double)(joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127;
    setLiftPower(up);
}