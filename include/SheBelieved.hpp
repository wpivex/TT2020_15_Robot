#pragma once
#include "main.h"
#include "Drive.hpp"
#include "Lift.hpp"
#include "Tilter.hpp"
using namespace okapi;

#define DRIVE_LEFT_FRONT 18
#define DRIVE_LEFT_MID 17
#define DRIVE_LEFT_BACK 19
#define DRIVE_RIGHT_FRONT 8
#define DRIVE_RIGHT_MID 9
#define DRIVE_RIGHT_BACK 10

#define INTAKE_LEFT 11
#define INTAKE_RIGHT 1
#define INTAKE_LEFT_2 3
#define INTAKE_RIGHT_2 15

#define FOURBAR_LEFT 20
#define FOURBAR_RIGHT 7

#define ARM_LEFT 14
#define ARM_RIGHT 5

#define ENCODER_LEFT_DRIVE_TOP 'c'
#define ENCODER_LEFT_DRIVE_BOT 'd'
#define ENCODER_RIGHT_DRIVE_TOP 'e'
#define ENCODER_RIGHT_DRIVE_BOT 'f'


class SheBelieved {
	private:
		static SheBelieved* robot;
		SheBelieved();
		int lastUp = 0;
		int lastDown = 0;
		double fourbarMinVel = 25;
		double fourbarUpValue = 625; //when tray is 90 deg
		double fourbarGain = 0.8;

		double armStopPos = 5;
	public:
		static SheBelieved* getRobot();
		std::shared_ptr<MotorGroup> intake;
		std::shared_ptr<Tilter> tilter;
		std::shared_ptr<Lift> lift;
		std::shared_ptr<Drive> drive;
		void opControlIntake(pros::Controller& joystick);
		void opControl(pros::Controller& joystick);
		void runIntake(int power);
		void runArm(int power);
		void armUp(int vel=50);
		void armDown(int vel=50);
};
