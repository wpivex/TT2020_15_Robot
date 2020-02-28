#pragma once
#include "main.h"



using namespace okapi;

enum DrivePrecision{
    HIGH_PRECISION,
    MEDIUM_PRECISION,
    NO_PRECISION
};

class Drive {
	public:
		Drive();
		std::shared_ptr<okapi::DefaultOdomChassisController> chassis;
		std::shared_ptr<okapi::ChassisControllerPID> chassisPID;
		std::shared_ptr<okapi::ADIEncoder> leftEncoder, rightEncoder;

		void opControl(pros::Controller& joystick);
		void turnToAngle(QAngle angle, int vel, DrivePrecision precision);
		void driveDist(QLength len, int vel, DrivePrecision precision=HIGH_PRECISION);
		void setTurnsMirrored(bool mirror);
		void moveLeft(int power);
		void moveRight(int power);
	private:
		std::shared_ptr<MotorGroup> leftMotors;
		std::shared_ptr<MotorGroup> rightMotors;
		std::vector<std::tuple<int16_t, int16_t>> leftMotorPorts;
		std::vector<std::tuple<int16_t, int16_t>> rightMotorPorts;
		QLength getOrientedError();

		bool turnsMirrored = false;
		// save values of where you want to be (but not neccesarily are)
        QLength x_d = 0_in;
        QLength y_d = 0_in;
        QAngle t_d = 0_deg;

		// threshold 
		double NO_PRECISION_TURN_THRESH = 2.0;
};
