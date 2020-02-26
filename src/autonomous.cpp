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
	// robot->drive->chassis->getModel()->setMaxVelocity(100);

	// SET COLOR
	#ifdef BLUE
	robot->drive->chassis->setTurnsMirrored(false);
	#endif

	#ifdef RED
	robot->drive->chassis->setTurnsMirrored(true);
	#endif

	// Deploy

	// line up with stack of 4.
	robot->lift->moveToPos(490,100);
	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0005, 0.000003, 0.00000001},
		{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(48.7_in);
	robot->drive->chassis->turnToAngle(122_deg);

	// back up a little
	robot->drive->chassisPID->setGains(
		{0.00018, 0.00008, 0.00000028},
		{0.0005, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistanceAsync(-10_in);
	pros::delay(1100);
	robot->lift->moveToPos(0,100);
	robot->tilter->moveFourbar(-40);
	robot->drive->chassis->waitUntilSettled();
	robot->drive->chassis->moveDistance(10_in);

	// zoom to stack of 4.
	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0005, 0.000004, 0.00000001},
		{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	);
	robot->runIntake(200);
	robot->drive->chassis->moveDistance(30_in);
	robot->tilter->moveFourbar(0);
	robot->lift->setLiftPower(0);

	// get preload and cube infront of preload
	robot->drive->chassisPID->setGains(
		{0.00018, 0.00008, 0.00000028},
		{0.0005, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(-10_in);
	robot->drive->chassis->turnToAngle(224_deg);
	robot->lift->moveToPos(45,30);
	robot->drive->chassis->setMaxVelocity(200);
	robot->drive->chassisPID->setGains(
		{0.00022, 0.0001, 0.00000028},
		{0.0005, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(35_in);

	//pick up cube on side of close tower
	robot->lift->moveToPos(0,30);
	robot->drive->chassis->setMaxVelocity(200);
	robot->drive->chassis->turnToAngle(80_deg);
	robot->lift->moveToPos(45,30);
	robot->drive->chassisPID->setGains(
		{0.00018, 0.00008, 0.00000028},
		{0.0005, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(10_in);
	robot->lift->moveToPos(0,30);

	//back up anreposition
	robot->drive->chassis->turnToAngle(60_deg);
	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0005, 0.000004, 0.00000001},
		{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(-14_in);
	robot->drive->chassis->turnToAngle(110_deg);

	// get cube behind twer
	robot->lift->moveToPos(45,30);
	robot->drive->chassis->moveDistance(19_in);
	robot->lift->moveToPos(0,30);

	// reposition and get cube near barrier
	robot->drive->chassis->moveDistance(-15_in);
	robot->drive->chassis->turnToAngle(-95_deg);
	robot->lift->moveToPos(45,30);
	robot->drive->chassis->moveDistance(20_in);
	robot->lift->moveToPos(0,30);


	robot->runIntake(0);

	
}
