#include "main.h"

class Lift {
public:
  Lift();

  void run(pros::Controller &controller);
private:
  std::shared_ptr<okapi::MotorGroup> liftMotor;
};
