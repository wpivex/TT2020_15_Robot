#pragma once
#include "main.h"


using namespace okapi;

class Drive {
	public:
		Drive();
		std::shared_ptr<okapi::OdomChassisController> chassis;
		void opControl(pros::Controller& joystick);
		std::shared_ptr<okapi::ADIEncoder> leftEncoder, rightEncoder;
	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
};
