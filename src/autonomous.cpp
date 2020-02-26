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

	// robot->lift->moveToPos(355, 50);
	// pros::delay(1000);
	// robot->runIntake(200);
	robot->runIntake(200);
	pros::delay(200);
	robot->drive->chassis->moveDistance(20_in);
	robot->drive->chassis->turnToAngle(122_deg); //90 deg right
	robot->drive->chassis->moveDistance(13_in); //CUBE ONE
	robot->drive->chassis->turnToAngle(25_deg);
	robot->lift->moveToPos(45,30);
	robot->drive->chassis->moveDistance(14_in); //CUBE 2
	// pros::delay(200); //get 3 + 1 cube
	robot->lift->moveToPos(0,30);
	robot->drive->chassis->moveDistance(-35_in);
	robot->drive->chassis->turnToAngle(95_deg);

	robot->lift->moveToPos(45,30);
	robot->drive->chassis->moveDistance(20_in); //got side cube
	// robot->drive->chassis->moveDistance(5_in); //got side cube
	robot->lift->moveToPos(0,30);

	robot->drive->chassis->moveDistance(-20_in);

	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0005, 0.000004, 0.00000001},
		{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	);

	robot->drive->chassis->turnToAngle(-55_deg);
	robot->drive->chassis->moveDistance(60_in); //zoom


	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0006, 0.000003, 0.000}, //chaing turns
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);

	robot->drive->chassis->turnToAngle(83_deg);

//MID mid cube
	robot->lift->moveToPos(45,30);
	robot->drive->chassis->moveDistance(17_in); //got side cube
	robot->lift->moveToPos(0,30);

	robot->drive->chassisPID->setGains(
		{0.00018, 0.00008, 0.00000028},
		{0.0006, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(-17_in);
	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0006, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->turnToAngle(40_deg);

//LEFT cube of left tower
	robot->lift->moveToPos(45,30);
	robot->drive->chassis->moveDistance(15_in); //got side cube
	robot->lift->moveToPos(0,30);

	robot->drive->chassisPID->setGains(
		{0.00018, 0.00008, 0.00000028},
		{0.0006, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);
	robot->drive->chassis->moveDistance(-16_in);
	robot->drive->chassisPID->setGains(
		{0.00022, 0.00011, 0.00000038},
		{0.0006, 0.000003, 0.000},
		{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	);

	robot->drive->chassis->turnToAngle(110_deg);

//ram into stack
	robot->drive->chassis->moveDistance(28_in);

	// back up and go to last cube
	robot->drive->chassis->turnToAngle(260_deg);

	robot->drive->chassis->moveDistance(40_in);
	// robot->drive->chassis->getModel()->setMaxVelocity(50);

	// pros::delay(1000);
	//
	// robot->drive->chassisPID->setGains(
	// 	{0.00022, 0.00011, 0.00000038},
	// 	{0, 0, 0.000},
	// 	{0, 0, 0.000} // Angle controller gains (helps drive straight)
	// );



	// DEPLOY

}
