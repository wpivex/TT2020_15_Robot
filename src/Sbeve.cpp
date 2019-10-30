#include "Sbeve.hpp"

Sbeve* Sbeve::instance = NULL;
Drivetrain Sbeve::drivetrain;
Lift Sbeve::lift;

Sbeve::Sbeve() {}

Sbeve* Sbeve::getSbeve() {
	if(instance == NULL) {
		instance = new Sbeve();
	}
	return instance;
}

void Sbeve::drive(pros::Controller &controller) {
	drivetrain.drive(controller);
}

void Sbeve::runLift(pros::Controller &controller) {
	lift.run(controller);
}
