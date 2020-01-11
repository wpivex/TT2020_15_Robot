#include "main.h"
#include "hamburger.hpp"

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
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	auto robot = Hamburger::getRobot();
	robot->drive->chassis->getModel()->setMaxVelocity(50);


	// robot->arm->moveAbsolute(300, 70);
	// robot->drive->chassis->moveDistance(900);
	// pros::delay(500);
	// robot->drive->chassis->moveDistance(-800);
	// pros::delay(2000);

	// DEPLOY
	robot->armUp(200);
	pros::delay(1500);
	robot->armDown(200);
	pros::delay(1500);

	// Move forward, kick cube in way
	robot->runIntake(-100);
	robot->drive->chassis->moveDistance(2450);
	// Turn to stack
	robot->drive->chassis->turnAngle(-100_deg);
	robot->armUp();
	pros::delay(1000);
	robot->runIntake(200);
	// Move fwd to stack
	robot->drive->chassis->moveDistance(450);
	pros::delay(1000);
	// Pick up v stack while moving
	robot->drive->chassis->moveDistanceAsync(300);
	robot->armDown(200);
	pros::delay(1000);
	// move back, tur, move up to grab cube
	robot->drive->chassis->moveDistance(-200);
	robot->drive->chassis->turnAngle(80_deg);
	robot->drive->chassis->moveDistance(580);// 550
	// move back and turn
	robot->drive->chassis->moveDistance(-580);
	robot->drive->chassis->turnAngle(155_deg);
	// Pick up other cube maybe
	robot->drive->chassis->moveDistance(600);//!!!
	robot->drive->chassis->moveDistance(-600);
	// Turn and pick up last cube before preload
	robot->drive->chassis->turnAngle(125_deg);
	robot->drive->chassis->moveDistance(1100);
	// Swing turn ish in to catch cube if it's caught at a diagonal
	robot->drive->chassis->moveDistanceAsync(200);
	pros::delay(200);// yeah I know - it's fine
	robot->drive->chassis->turnAngle(-80_deg);
	// Pick up preload
	robot->drive->chassis->moveDistance(1000);
	robot->drive->chassis->moveDistance(-200);
	// Swing turn towards goal
	robot->drive->chassis->turnAngle(-50_deg);
	pros::delay(2000);
	// Go for the goal!
	robot->drive->chassis->moveDistance(900);
	robot->drive->chassis->turnAngle(-50_deg);





	// robot->drive->chassis->moveDistance(24_in);

	// robot->intake->moveVelocity(200);
	// robot->arm->moveAbsolute(10, 30);

	// robot->drive->chassis->driveToPoint({24_in,24_in});
	// robot->drive->chassis->stop();

	// robot->runIntake(100);
	// robot->drive->chassis->getModel()->setMaxVelocity(55);

	// robot->drive->chassis->moveDistance(38_in);
	// pros::delay(100);

	// robot->drive->chassis->getModel()->setMaxVelocity(110);
	// robot->drive->chassis->turnAngle(45_deg);
	// robot->runIntake(200);
	// robot->drive->chassis->getModel()->setMaxVelocity(60);
	// robot->drive->chassis->moveDistance(20_in);
	// pros::delay(2000);

	// robot->drive->chassis->getModel()->setMaxVelocity(110);
	// robot->drive->chassis->moveDistance(-30_in);
	// robot->runIntake(0);

	// robot->drive->chassis->turnAngle(125_deg);

	// pros::delay(500);

	// robot->drive->chassis->moveDistance(17_in);
	// pros::delay(500);

	// robot->tiltFourbarScore();

	// pros::delay(5000);

	// robot->runIntake(-50);
	// pros::delay(250);
	// robot->drive->chassis->moveDistance(-15_in);

	// robot->tiltFourbarRetract();

}

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
	auto robot = Hamburger::getRobot();
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
				printf("%d,%d\n",vals[0],vals[1]);
				robot->drive->chassis->getModel()->resetSensors();
				pros::delay(200);
			}
		#endif

		pros::delay(20);
	}
}
