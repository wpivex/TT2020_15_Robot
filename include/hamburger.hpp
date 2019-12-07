#pragma once
#include "main.h"
#include "drive.hpp"
#include "brainDriver.hpp"
using namespace okapi;

#define DRIVE_LEFT_FRONT 20
#define DRIVE_LEFT_MID_FRONT 18
#define DRIVE_LEFT_MID_BACK 17
#define DRIVE_LEFT_BACK 19
#define DRIVE_RIGHT_FRONT 0
#define DRIVE_RIGHT_MID_FRONT 8
#define DRIVE_RIGHT_MID_BACK 9
#define DRIVE_RIGHT_BACK 10

#define INTAKE_LEFT 11
#define INTAKE_RIGHT 1

#define FOURBAR_LEFT 14
#define FOURBAR_RIGHT 5

#define ENCODER_LEFT_DRIVE_TOP 'a'
#define ENCODER_LEFT_DRIVE_BOT 'b'
#define ENCODER_RIGHT_DRIVE_TOP 'c'
#define ENCODER_RIGHT_DRIVE_BOT 'd'


class Hamburger {
	private:
		static Hamburger* robot;
		std::shared_ptr<MotorGroup> intake;
		std::shared_ptr<MotorGroup> fourbar;
		std::shared_ptr<MotorGroup> tilt;
		Hamburger();
		int lastUp = 0;
		int lastDown = 0;
		double fourbarThreshold = 500;
		double fourbarUpValue = 930;
	public:
		static Hamburger* getRobot();
		std::shared_ptr<Drive> drive;
		std::shared_ptr<BrainDriver> brainDriver;
		void opControlIntake(pros::Controller& joystick);
		void opControlFourbar(pros::Controller& joystick);
		void opControlTilt(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void runTilt(int power);
		void moveFourbar(int power);
		void tiltFourbarScore();
		void tiltFourbarRetract();
};
