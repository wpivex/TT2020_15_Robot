#include "Lift.hpp"

Lift::Lift() {

  liftMotor = std::make_shared<okapi::MotorGroup> ({okapi::Motor(LIFT_RIGHT,false,okapi::AbstractMotor::gearset::green),
      okapi::Motor(LIFT_RIGHT,true,okapi::AbstractMotor::gearset::green)});

  liftMotor->setGearing(okapi::AbstractMotor::gearset::green);
  liftMotor->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void Lift::run(pros::Controller &joystick) {
  liftMotor->moveVelocity(200*joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127.0);
}
