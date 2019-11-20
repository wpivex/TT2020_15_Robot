#include "lift.hpp"
#include "sbeve.hpp"

Lift::Lift() {
    MotorGroup left({Motor(LIFT_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees));
    MotorGroup right({Motor(LIFT_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees));
    leftMotors = std::make_shared<MotorGroup>(left);
    rightMotors = std::make_shared<MotorGroup>(right);
    leftMotors->setBrakeMode(AbstractMotor::brakeMode::hold);
    rightMotors->setBrakeMode(AbstractMotor::brakeMode::hold);
}
