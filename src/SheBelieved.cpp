#include "SheBelieved.hpp"

SheBelieved *SheBelieved::robot = NULL;
SheBelieved *SheBelieved::getRobot() {
	if (robot == NULL) {
		robot = new SheBelieved();
	}
	return robot;
}

SheBelieved::SheBelieved() {
	drive = std::make_shared<Drive>();
	lift = std::make_shared<Lift>();
	tilter = std::make_shared<Tilter>();

	MotorGroup intakeMotors({Motor(INTAKE_LEFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 						 Motor(INTAKE_RIGHT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
												 	 Motor(INTAKE_LEFT_2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
											     Motor(INTAKE_RIGHT_2, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);
}

void SheBelieved::opControl(pros::Controller &joystick) {
	drive->opControl(joystick);
	lift->opControl(joystick);
	tilter->opControl(joystick);
	opControlIntake(joystick);
}

void SheBelieved::runIntake(int power) {
	intake->moveVelocity(power);
}

void SheBelieved::opControlIntake(pros::Controller &joystick) {
	int l1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
	int l2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
	int u  = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

	if (l2) {
		runIntake(200);
	}
	else if (l1) {
		runIntake(-200);
	} else if (u) {
		runIntake(-100);
	}
	else {
		runIntake(0);
	}
}
