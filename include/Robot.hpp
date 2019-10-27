# pragma once
# include "main.h"
#include "Drivetrain.hpp"

class Robot {
	public:
		static Robot* getRobot();
		void drive(pros::Controller &controller);
		void runLift(pros::Controller &controller);
	private:
		Robot();
		static Robot* instance;
		static Drivetrain drivetrain;
		static Lift lift;
};
