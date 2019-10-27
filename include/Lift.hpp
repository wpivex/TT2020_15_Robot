#include "main.h"

class Lift {
public:
  Lift();

  void run(pros::Controller &controller);
private:
  std::shared_ptr<okapi::MotorGroup> lift;

  std::initializer_list<okapi::Motor> liftMotors;
};
