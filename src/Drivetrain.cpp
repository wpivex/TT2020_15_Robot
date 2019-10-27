#include "Drivetrain.hpp"

Drivetrain::Drivetrain() {
  leftDriveMotors = {okapi::Motor(DRIVE_LEFT_FRONT_PORT,false,okapi::AbstractMotor::gearset::green),
                      okapi::Motor(DRIVE_LEFT_BACK_PORT,false,okapi::AbstractMotor::gearset::green),
                      okapi::Motor(DRIVE_LEFT_MID_PORT,true,okapi::AbstractMotor::gearset::green)};
   rightDriveMotors = {okapi::Motor(DRIVE_RIGHT_FRONT_PORT,true,okapi::AbstractMotor::gearset::green),
                      okapi::Motor(DRIVE_RIGHT_BACK_PORT,true,okapi::AbstractMotor::gearset::green),
                      okapi::Motor(DRIVE_RIGHT_MID_PORT,false,okapi::AbstractMotor::gearset::green)};

  driveLeft = std::make_shared<okapi::MotorGroup>(leftDriveMotors);
  driveRight = std::make_shared<okapi::MotorGroup>(rightDriveMotors);

  leftEnc = std::make_shared<okapi::ADIEncoder>(DRIVE_LEFT_ENC_TOP,DRIVE_LEFT_ENC_BOT,true);
  rightEnc = std::make_shared<okapi::ADIEncoder>(DRIVE_RIGHT_ENC_TOP, DRIVE_RIGHT_ENC_BOT,true);

  driveLeft->setGearing(okapi::AbstractMotor::gearset::green);
  driveRight->setGearing(okapi::AbstractMotor::gearset::green);
  driveLeft->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  driveRight->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

  chassisController = okapi::ChassisControllerFactory::createPtr(driveLeft, driveRight, leftEnc, rightEnc,
                                                                  AbstractMotor::gearset::green,
                                                                  {4.125_in ,11.5_in});
}

void Drivetrain::drive(pros::Controller &joystick) {
  chassisController->tank(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127.0,
                          joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/127.0);
}
