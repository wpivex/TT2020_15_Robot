# pragma once
# include "main.h"
# include "Drivetrain.hpp"
# include "Lift.hpp"

class Sbeve {
	public:
		static Sbeve* getSbeve();
		void drive(pros::Controller &controller);
		void runLift(pros::Controller &controller);
	private:
		Sbeve();
		static Sbeve* instance;
		static Drivetrain drivetrain;
		static Lift lift;
};
