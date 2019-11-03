#include "Lift.hpp"

Lift::Lift() {

  okapi:MotorGroup tempGroup
  ({okapi::Motor(LIFT_RIGHT,false,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees),
    okapi::Motor(LIFT_RIGHT,true,okapi::AbstractMotor::gearset::green,okapi::AbstractMotor::encoderUnits::degrees)});

  liftMotor = std::make_shared<okapi::MotorGroup> (tempGroup);

//   liftMotor = std::make_shared<okapi::MotorGroup> (({okapi::Motor(LIFT_RIGHT,false,okapi::AbstractMotor::gearset::green),
      // okapi::Motor(LIFT_RIGHT,true,okapi::AbstractMotor::gearset::green)}));

  liftMotor->setGearing(okapi::AbstractMotor::gearset::green);
  liftMotor->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void Lift::run(pros::Controller &joystick) {
  liftMotor->moveVelocity(200*joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127.0);
}
