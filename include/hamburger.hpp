#pragma once
#include "main.h"
#include "drive.hpp"
#include "brainDriver.hpp"
using namespace okapi;

#define DRIVE_LEFT_FRONT 18
#define DRIVE_LEFT_MID 17
#define DRIVE_LEFT_BACK 19
#define DRIVE_RIGHT_FRONT 8
#define DRIVE_RIGHT_MID 9
#define DRIVE_RIGHT_BACK 10

#define INTAKE_LEFT 11
#define INTAKE_RIGHT 1

#define FOURBAR_LEFT 20
#define FOURBAR_RIGHT 7

#define ARM_LEFT 14
#define ARM_RIGHT 5

// #define ENCODER_LEFT_DRIVE_TOP 'e'
// #define ENCODER_LEFT_DRIVE_BOT 'f'
// #define ENCODER_RIGHT_DRIVE_TOP 'c'
// #define ENCODER_RIGHT_DRIVE_BOT 'd'


class Hamburger {
	private:
		static Hamburger* robot;
		Hamburger();
		int lastUp = 0;
		int lastDown = 0;
		double fourbarMinVel = 25;
		double fourbarUpValue = 600; //when tray is 90 deg
		double fourbarGain = 0.70;

		double armStopPos = 5;
	public:
		static Hamburger* getRobot();
		std::shared_ptr<MotorGroup> intake;
		std::shared_ptr<MotorGroup> fourbar;
		std::shared_ptr<MotorGroup> arm;
		std::shared_ptr<Drive> drive;
		std::shared_ptr<BrainDriver> brainDriver;
		void opControlIntake(pros::Controller& joystick);
		void opControlFourbar(pros::Controller& joystick);
		void opControlArm(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void runArm(int power);
		void armUp(int vel=50);
		void armDown(int vel=50);
		void moveFourbar(int power);
		void tiltFourbarScore();
		void tiltFourbarRetract();
};
