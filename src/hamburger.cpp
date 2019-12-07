#include "hamburger.hpp"

Hamburger *Hamburger::robot = NULL;
Hamburger *Hamburger::getRobot() {
	if (robot == NULL) {
		robot = new Hamburger();
	}
	return robot;
}

Hamburger::Hamburger() {
	drive = std::make_shared<Drive>();

	MotorGroup intakeMotors({Motor(INTAKE_LEFT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 						 Motor(INTAKE_RIGHT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);

	MotorGroup fourbarMotors({Motor(FOURBAR_RIGHT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
						  							Motor(FOURBAR_LEFT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);

	MotorGroup tiltMotors({Motor(DRIVE_LEFT_FRONT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
						  							Motor(DRIVE_RIGHT_FRONT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	tilt = std::make_shared<MotorGroup>(tiltMotors);

	// brainDriver = std::make_shared<BrainDriver>(BrainDriver());
}

void Hamburger::opControl(pros::Controller &joystick) {
	drive->opControlDrive(joystick);
	opControlFourbar(joystick);
	opControlIntake(joystick);
	opControlTilt(joystick);
}

void Hamburger::runIntake(int power) {
	intake->moveVelocity(power);
}

void Hamburger::runTilt(int power) {
	tilt->moveVelocity(power);
}

void Hamburger::opControlTilt(pros::Controller &joystick) {
	int r1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
	int r2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

	if (r1) {
		runTilt(200);
	}
	else if (r2) {
		runTilt(-200);
	}
	else {
		runTilt(0);
	}
}

void Hamburger::opControlIntake(pros::Controller &joystick) {
	int r1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
	int r2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
	int l1 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
	int l2 = joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

	if (l2) {
		runIntake(200);
	}
	else if (l1) {
		runIntake(-200);
	}
	else {
		runIntake(0);
	}
}

void Hamburger::opControlFourbar(pros::Controller& joystick) {
	// if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
	// 	moveFourbar(100);
	// } else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
	// 	moveFourbar(-100);
	// } else {
	// 	moveFourbar(0);
	// }
	moveFourbar(-joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
}

void Hamburger::moveFourbar(int power) {
	// if going up, throttle the value
	if(power > 0) {
		double numerator = fourbarUpValue - fourbar->getPosition() * 2 / 3;
		double ratio = (double)(abs(numerator)) / fourbarUpValue;
		fourbar->moveVelocity(power * ratio);
	} else {
		// full speed down
		fourbar->moveVelocity(power);
	}
}

void Hamburger::tiltFourbarScore() {
	fourbar->tarePosition();
	fourbar->moveRelative(fourbarUpValue,100);
}

void Hamburger::tiltFourbarRetract() {
	// fourbar->tarePosition();
	fourbar->moveRelative(fourbarUpValue,100);
}
