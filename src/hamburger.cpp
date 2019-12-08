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

	MotorGroup intakeMotors({Motor(INTAKE_LEFT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
							 						 Motor(INTAKE_RIGHT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	intakeMotors.setBrakeMode(AbstractMotor::brakeMode::brake);
	intake = std::make_shared<MotorGroup>(intakeMotors);

	MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
						  							Motor(FOURBAR_RIGHT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);
	fourbar->setBrakeMode(AbstractMotor::brakeMode::coast);

	MotorGroup armMotors({Motor(ARM_LEFT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
						  							Motor(ARM_RIGHT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	armMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
	arm = std::make_shared<MotorGroup>(armMotors);

	// brainDriver = std::make_shared<BrainDriver>(BrainDriver());
}

void Hamburger::opControl(pros::Controller &joystick) {
	drive->opControlDrive(joystick);
	opControlFourbar(joystick);
	opControlIntake(joystick);
	opControlArm(joystick);
}

void Hamburger::runIntake(int power) {
	intake->moveVelocity(power);
}

void Hamburger::runArm(int power) {
	arm->moveVelocity(power);
}

void Hamburger::opControlArm(pros::Controller &joystick) {
	arm->moveVelocity(joystick.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
}

void Hamburger::opControlIntake(pros::Controller &joystick) {
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

void Hamburger::moveFourbar(int power) {
	// if going up, throttle the value
	if(power > 0) {
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

	} else {
		// full speed down
		fourbar->moveVelocity(power);
	}
}

void Hamburger::opControlFourbar(pros::Controller& joystick) {
	if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		moveFourbar(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}
}
