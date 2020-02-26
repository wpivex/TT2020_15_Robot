#pragma once
#include "main.h"

using namespace okapi;

class Lift {
	public:
		Lift();
		void setLiftPower(int velocity);
		void opControl(pros::Controller& joystick);
		void moveToPos(int pos, int speed);
		std::shared_ptr<MotorGroup> armMotors;
	private:
};
