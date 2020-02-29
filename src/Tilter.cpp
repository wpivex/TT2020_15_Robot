#include "Tilter.hpp"
#include "SheBelieved.hpp"

Tilter::Tilter() {
    MotorGroup fourbarMotors({Motor(FOURBAR_LEFT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees),
						  							Motor(FOURBAR_RIGHT, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees)});
	fourbar = std::make_shared<MotorGroup>(fourbarMotors);
	fourbar->setBrakeMode(AbstractMotor::brakeMode::coast);
}

 void Tilter::opControl(pros::Controller& joystick) {
     if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		moveFourbar(100);
	} else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		moveFourbar(-100);
	} else {
		moveFourbar(0);
	}
 }

 void Tilter::tiltFourbarScore() {
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

void Tilter::tiltFourbarRetract() {
	// fourbar->tarePosition();
	fourbar->moveAbsolute(0,100);
}

void Tilter::moveFourbar(int power) {
	// if going up, throttle the value
	double fourbarPos = fourbar->getPosition();
    double diff = fourbarUpValue - fourbarPos;
	if(power > 0) {
		if(diff < 0) {
			fourbar->moveAbsolute(fourbarUpValue, 100);
		} else {
			int velocity = diff * fourbarGain;
        	velocity = velocity < fourbarMinVel ? fourbarMinVel : velocity;

			// fourbar->moveVelocity(velocity);
			pros::c::motor_move_velocity(FOURBAR_RIGHT, -1 * velocity);
			pros::c::motor_move_velocity(FOURBAR_LEFT, velocity);
		}
	} else if(power < 0) {
		// full speed down
		fourbar->moveVelocity(power);
	} else {
		if(diff < 0) {
			fourbar->moveAbsolute(fourbarUpValue,100);
		} else {
			fourbar->moveVoltage(0);
		}
	}
}