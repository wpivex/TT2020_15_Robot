#include "main.h"

class CubeTube {
public:
  CubeTube();

  void run(pros::Controller &controller);

private:
  std::shared_ptr<okapi::Motor> tubeMotor;
};
