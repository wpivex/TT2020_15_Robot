#include "Lift.hpp"

Lift::Lift() {
  liftMotors = {okapi::Motor(LIFT_RIGHT,false,okapi::AbstractMotor::gearset::green),
                      okapi::Motor(LIFT_RIGHT,true,okapi::AbstractMotor::gearset::green)};

  lift = std::make_shared<okapi::MotorGroup>(liftMotors);

  lift->setGearing(okapi::AbstractMotor::gearset::green);
  lift->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void Lift::run(pros::Controller &joystick) {
  lift->moveVelocity(200*joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127.0);
}
