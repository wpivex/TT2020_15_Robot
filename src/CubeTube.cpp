#include "CubeTube.hpp"

CubeTube::CubeTube() {
  tubeMotor = std::make_shared<okapi::Motor>((okapi::Motor(CUBE_TUBE,false,okapi::AbstractMotor::gearset::green)));


  tubeMotor->setGearing(okapi::AbstractMotor::gearset::green);
  tubeMotor->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void CubeTube::run(pros::Controller &joystick) {
  tubeMotor->moveVelocity(200*joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/127.0);
}
