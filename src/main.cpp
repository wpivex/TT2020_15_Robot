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
	robot->drive->chassis->stop();
	// ADIEncoder encL(ENCODER_LEFT_DRIVE_TOP,ENCODER_LEFT_DRIVE_BOT,false);
	// ADIEncoder encR(ENCODER_RIGHT_DRIVE_TOP,ENCODER_RIGHT_DRIVE_BOT,true);
	// encL.reset();
	// encR.reset();

	// auto leftFront = pros::Motor(DRIVE_LEFT_FRONT, true);
	// auto leftMid = pros::Motor(DRIVE_LEFT_MID, false);
	// auto leftBack = pros::Motor(DRIVE_LEFT_BACK, true);
	// auto rightFront = pros::Motor(DRIVE_RIGHT_FRONT, false);
	// auto rightMid = pros::Motor(DRIVE_RIGHT_MID, true);
	// auto rightBack = pros::Motor(DRIVE_RIGHT_BACK, false);

	while (true) {
		robot->opControl(master);
		std::valarray<std::int32_t> vals = robot->drive->chassis->getModel()->getSensorVals();
		// printf("L: %d, R: %d, isSettled: %d\n", vals[0], vals[1], robot->drive->chassis->isSettled());
		auto state = robot->drive->chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
		Menu::getMenu()->addDebugPrint(0, state.str());
		Menu::getMenu()->addDebugPrint(1, "L: " + std::to_string(vals[0]));
		Menu::getMenu()->addDebugPrint(2, "R: " + std::to_string(vals[1]));
		Menu::getMenu()->addDebugPrint(3, "Arm: " + std::to_string((int)robot->lift->armMotors->getPosition()));

		// double forward = (double)(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    	// double turn = (double)(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		// leftFront.move(forward + turn*0.7);
		// leftMid.move(forward + turn*0.7);
		// leftBack.move(forward + turn*0.7);
		// rightFront.move(forward - turn*0.7);
		// rightMid.move(forward - turn*0.7);
		// rightBack.move(forward - turn*0.7);




		pros::delay(20);
	}
}
