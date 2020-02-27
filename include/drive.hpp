#pragma once
#include "main.h"


using namespace okapi;

enum DrivePrecision{
    HIGH_PRECISION,
    MEDIUM_PRECISION,
    WHAT_PRECISION
};

class Drive {
	public:
		Drive();
		std::shared_ptr<okapi::DefaultOdomChassisController> chassis;
		std::shared_ptr<okapi::ChassisControllerPID> chassisPID;
		std::shared_ptr<okapi::ADIEncoder> leftEncoder, rightEncoder;

		void opControl(pros::Controller& joystick);
		void turnToAngle(QAngle angle, int vel, DrivePrecision precision);
		void driveDist(QLength len, int vel, DrivePrecision precision);
		void setTurnsMirrored(bool mirror);
	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
		std::vector<std::tuple<int16_t, int16_t>> leftMotorPorts;
		std::vector<std::tuple<int16_t, int16_t>> rightMotorPorts;
		bool turnsMirrored = false;
        QLength x_d = 0_in;
        QLength y_d = 0_in;
        QAngle t_d = 0_deg;

		void moveLeft(int power);
		void moveRight(int power);
};
