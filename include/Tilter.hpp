#pragma once
#include "main.h"

using namespace okapi;

class Tilter {
    private:
        double fourbarMinVel = 0;
		double fourbarUpValue = 600; //when tray is 90 deg
    public:
        Tilter();
    	double fourbarGain = 0.13;
        std::shared_ptr<MotorGroup> fourbar;

        void opControl(pros::Controller& joystick);
        void tiltFourbarScore();
        void tiltFourbarRetract();
        void moveFourbar(int power);
};
