#pragma once
#include "main.h"


using namespace okapi;

class Lift {
	public:
		setLiftPower();
	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
};
