#include "main.h"
#include "Sbeve.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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
	auto robot = Sbeve::getRobot();
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
			// printf("%d,%d\n",vals[0],vals[1]);
			sprintf(lcdText, "L: %4d R: %4d", vals[0], vals[1]);
			sprintf(armPos, "Arm: %4f", robot->arm->getPosition());
			// sprintf(lcdText[1], "Right: %d", vals[1]);
			// pros::lcd::set_text(2, "Left");
			pros::lcd::set_text(2, lcdText);
			pros::lcd::set_text(3, armPos);
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
				// printf("%d,%d\n",vals[0],vals[1]);
				robot->drive->chassis->getModel()->resetSensors();
				pros::delay(200);
			}
		#endif

		pros::delay(20);
	}
}
