#pragma once
#include "main.h"

using namespace okapi;

class Tilter {
    private:
        double fourbarMinVel = 0;
		double fourbarUpValue = 625; //when tray is 90 deg
        std::shared_ptr<MotorGroup> fourbar;
    public:
        Tilter();
    		double fourbarGain = 0.18;
        void opControl(pros::Controller& joystick);
        void tiltFourbarScore();
        void tiltFourbarRetract();
        void moveFourbar(int power);
};
