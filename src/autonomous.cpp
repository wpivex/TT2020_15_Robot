#include "SheBelieved.hpp"
#include "main.h"
#include "menu/Menu.hpp"

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
	auto robot = SheBelieved::getRobot();
	auto menu = Menu::getMenu();
	robot->drive->chassis->getModel()->setMaxVelocity(75);

	// SET COLOR
	#ifdef BLUE
	robot->drive->chassis->setTurnsMirrored(false);
	#endif

	#ifdef RED
	robot->drive->chassis->setTurnsMirrored(true);
	#endif

	// robot->drive->chassis->moveDistanceAsync(24_in);
	// robot->drive->chassis->turnAngleAsync(90_deg);
	robot->runIntake(200);
	robot->drive->chassis->turnToPoint({0_in, 84_in});
	robot->drive->chassis->waitUntilSettled();
	auto state = robot->drive->chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
	Menu::getMenu()->printTerminal(state.str());
	robot->drive->chassis->driveToPoint({0_in, 84_in});
	robot->drive->chassis->waitUntilSettled();
	state = robot->drive->chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
	Menu::getMenu()->printTerminal(state.str());
	robot->drive->chassis->turnToPoint({-15_in, 65_in});
	robot->drive->chassis->waitUntilSettled();
	state = robot->drive->chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
	Menu::getMenu()->printTerminal(state.str());
	robot->drive->chassis->driveToPoint({-15_in, 65_in});

	while(!robot->drive->chassis->isSettled()) {
		std::valarray<std::int32_t> vals = robot->drive->chassis->getModel()->getSensorVals();
		state = robot->drive->chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
		Menu::getMenu()->addDebugPrint(0, state.str());
		Menu::getMenu()->addDebugPrint(1, "L: " + std::to_string(vals[0]));
		Menu::getMenu()->addDebugPrint(2, "R: " + std::to_string(vals[1]));
		pros::delay(10);
	}
	printf("done\n");
	state = robot->drive->chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
	printf(state.str().c_str());
	
	// DEPLOY

}