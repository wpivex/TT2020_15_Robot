#include "main.h"

class Drivetrain {
public:
  Drivetrain();

  void drive(pros::Controller &controller);
private:
  std::shared_ptr<okapi::MotorGroup> driveLeft;
  std::shared_ptr<okapi::MotorGroup> driveRight;
  std::shared_ptr<okapi::ADIEncoder> leftEnc;
  std::shared_ptr<okapi::ADIEncoder> rightEnc;

  std::shared_ptr<okapi::ChassisController> chassisController;

  std::initializer_list<okapi::Motor> leftDriveMotors;
  std::initializer_list<okapi::Motor> rightDriveMotors;
};
