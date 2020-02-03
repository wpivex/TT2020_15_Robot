#pragma once
#include "main.h"

using namespace okapi;

class Lift {
	public:
		Lift();
		void setLiftPower(int velocity);
		void opControl(pros::Controller& joystick);

		std::shared_ptr<MotorGroup> armMotors;
	private:
};
