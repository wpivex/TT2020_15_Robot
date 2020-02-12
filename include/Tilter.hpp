#pragma once
#include "main.h"

using namespace okapi;

class Tilter {
    private:
        double fourbarMinVel = 25;
		double fourbarUpValue = 625; //when tray is 90 deg
		double fourbarGain = 0.18;
        std::shared_ptr<MotorGroup> fourbar;
    public:
        Tilter();
        void opControl(pros::Controller& joystick);
        void tiltFourbarScore();
        void tiltFourbarRetract();
        void moveFourbar(int power);
};