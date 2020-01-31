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

	MotorGroup intakeMotors({Motor(INTAKE_LEFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 						 Motor(INTAKE_RIGHT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);

	MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
						  							Motor(FOURBAR_RIGHT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);
	fourbar->setBrakeMode(AbstractMotor::brakeMode::coast);
}

void SheBelieved::opControl(pros::Controller &joystick) {
	drive->opControlDrive(joystick);
	lift->opControl(joystick);
	opControlFourbar(joystick);
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

void SheBelieved::moveFourbar(int power) {
	// if going up, throttle the value
	if(power > 0) {
		pros::lcd::set_text(2, "Fourbar Pos: " + std::to_string(fourbar->getPosition()));
		double fourbarPos = fourbar->getPosition();
		double numerator = (fourbarUpValue - fourbarPos) * fourbarGain;
		double ratio = (double)(abs(numerator)) / fourbarUpValue;
		int velocity = power * ratio;
		printf("Ratio: %f\n",ratio);

		if(fourbarPos >= fourbarUpValue) {
			velocity = 0.0;
		}
		else if(velocity < fourbarMinVel) {
			velocity = fourbarMinVel;
		}

		fourbar->moveVelocity(velocity);

		pros::lcd::set_text(1, "Fourbar velocity: " + std::to_string(velocity));
	} else {
		// full speed down
		fourbar->moveVelocity(power);
	}
}

void SheBelieved::opControlFourbar(pros::Controller& joystick) {
	if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		moveFourbar(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}
}

void SheBelieved::tiltFourbarScore() {
	fourbar->tarePosition();

	for(int i = 0; i < 50; i++) {
		double numerator = (fourbarUpValue - fourbar->getPosition()) * fourbarGain;
		double ratio = (double)(abs(numerator)) / fourbarUpValue;
		int velocity = 100 * ratio;

		if(velocity < fourbarMinVel) {
			velocity = fourbarMinVel;
		}
		fourbar->moveVelocity(velocity);

		pros::delay(100);
	}

	pros::delay(500);
}

void SheBelieved::tiltFourbarRetract() {
	// fourbar->tarePosition();
	fourbar->moveAbsolute(0,100);
}