#pragma once
#include "main.h"


using namespace okapi;

class Drive {
	public:
		Drive();
		std::shared_ptr<okapi::DefaultOdomChassisController> chassis;
		std::shared_ptr<okapi::ChassisControllerPID> chassisPID;
		void opControl(pros::Controller& joystick);
		std::shared_ptr<okapi::ADIEncoder> leftEncoder, rightEncoder;
	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
		std::vector<int16_t> leftMotorPorts;
		std::vector<int16_t> rightMotorPorts;

		void moveLeft(int power);
		void moveRight(int power);
};
