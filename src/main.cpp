#include "main.h"
#include "menu/Menu.hpp"
#include "SheBelieved.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
#define AUTO_DEBUG 0
void opcontrol() {

	pros::Controller master(pros::E_CONTROLLER_MASTER);
	auto robot = SheBelieved::getRobot();
	auto Menu = Menu::getMenu();
	// ADIEncoder encL(ENCODER_LEFT_DRIVE_TOP,ENCODER_LEFT_DRIVE_BOT,false);
	// ADIEncoder encR(ENCODER_RIGHT_DRIVE_TOP,ENCODER_RIGHT_DRIVE_BOT,true);
	// encL.reset();
	// encR.reset();

	char lcdText[30], armPos[30];

	while (true) {
		robot->opControl(master);
		std::valarray<std::int32_t> vals = robot->drive->chassis->getModel()->getSensorVals();
		#if AUTO_DEBUG
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
				autonomous();
			}
			sprintf(lcdText, "L: %4d R: %4d", vals[0], vals[1]);
			sprintf(armPos, "Arm: %4f", robot->lift->armMotors->getPosition());
			pros::lcd::set_text(2, lcdText);
			pros::lcd::set_text(3, armPos);
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
				robot->drive->chassis->getModel()->resetSensors();
				pros::delay(200);
			}
		#endif

		pros::delay(20);
	}
}
