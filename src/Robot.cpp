#include "Robot.hpp"

Robot* Robot::instance = NULL;
Drivetrain Robot::drivetrain;

Robot::Robot() {}

Robot* Robot::getRobot() {
	if(instance == NULL) {
		instance = new Robot();
	}
	return instance;
}

void Robot::drive(pros::Controller &controller) {
	drivetrain.drive(controller);
}
