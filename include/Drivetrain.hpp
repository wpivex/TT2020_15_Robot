#include "main.h"

#define DRIVE_LEFT_BACK_PORT 18
#define DRIVE_LEFT_FRONT_PORT 20
#define DRIVE_LEFT_MID_PORT 19
#define DRIVE_RIGHT_BACK_PORT 14
#define DRIVE_RIGHT_FRONT_PORT 17
#define DRIVE_RIGHT_MID_PORT 16

#define DRIVE_RIGHT_ENC_TOP 5
#define DRIVE_RIGHT_ENC_BOT 6
#define DRIVE_LEFT_ENC_TOP 7
#define DRIVE_LEFT_ENC_BOT 8

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
