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
	//yee-haw beep boop
	// -Betty
	//
	// SET COLOR
	// #ifdef BLUE
	// robot->drive->setTurnsMirrored(true);
	// #endif

	// #ifdef RED
	// robot->drive->chassis->setTurnsMirrored(false);
	// #endif

	if(robot->onRed) {
		robot->drive->setTurnsMirrored(false);
	} else {
		robot->drive->setTurnsMirrored(true);
	}

	// Deploy
	// robot->runIntake(-200);
	// pros::delay(310);
	// robot->runIntake(0);

	// // line up with stack of 4.
	// robot->lift->moveToPos(490,100);
	// robot->tilter->fourbar->moveAbsolute(300,100);
	// pros::delay(1000);
	// robot->drive->chassisPID->setGains(
	// 	{0.00024, 0.00011, 0.00000038},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	// );
	// robot->drive->chassis->getModel()->forward(50);
	// pros::delay(500);
	// robot->drive->chassis->getModel()->stop();
	// robot->drive->chassis->getModel()->forward(50);
	// pros::delay(500);
	// robot->drive->chassis->getModel()->stop();

	
	// robot->drive->chassis->moveDistanceAsync(52.5_in);
	// // robot->tilter->moveFourbar(100);
	// robot->tilter->moveFourbar(-10);
	// robot->drive->chassis->waitUntilSettled();
	// robot->drive->turnToAngle(124_deg, 200, HIGH_PRECISION);

	// // back up a little
	// robot->drive->chassisPID->setGains(
	// 	{0.00025, 0.0001, 0.0000003},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	// );
	// robot->runIntake(200);
	// robot->drive->chassis->moveDistanceAsync(-10_in);
	// pros::delay(1100);
	// robot->lift->moveToPos(-30,100);
	// robot->tilter->moveFourbar(-40);
	// robot->drive->chassis->waitUntilSettled();
	// robot->drive->chassis->moveDistance(8_in);

	// // zoom to stack of 4.
	// robot->drive->chassisPID->setGains(
	// 	{0.00022, 0.00011, 0.00000038},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	// );
	// robot->drive->chassis->moveDistance(35_in);
	// robot->tilter->moveFourbar(0);
	// robot->lift->setLiftPower(0);

	// // get preload and cube infront of preload
	// robot->drive->chassisPID->setGains(
	// 	{0.0003, 0.00008, 0.00000028},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	// );
	// robot->drive->chassis->moveDistance(-13_in);
	// robot->drive->turnToAngle(237_deg, 200, HIGH_PRECISION);
	// robot->lift->moveToPos(-30,30);
	// robot->drive->chassis->setMaxVelocity(200);
	// robot->drive->chassisPID->setGains(
	// 	{0.00022, 0.0001, 0.00000028},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	// );
	// robot->drive->chassis->moveDistance(35_in);

	// //pick up cube on side of close tower
	// robot->lift->moveToPos(-30,30);
	// robot->drive->chassis->setMaxVelocity(200);
	// robot->drive->turnToAngle(80_deg, 200, HIGH_PRECISION);
	// robot->lift->moveToPos(-30,30);
	// robot->drive->chassisPID->setGains(
	// 	{0.00018, 0.00008, 0.00000028},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	// );
	// robot->drive->chassis->moveDistance(12_in);
	// robot->lift->moveToPos(-30,30);

	// //back up anreposition
	// robot->drive->turnToAngle(70_deg, 200, HIGH_PRECISION);
	// robot->drive->chassisPID->setGains(
	// 	{0.00022, 0.00011, 0.00000038},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	// );
	// robot->drive->chassis->moveDistance(-14_in);
	// robot->drive->turnToAngle(108_deg, 200, HIGH_PRECISION);


	// // get cube behind tower
	// robot->lift->moveToPos(0,30);
	// robot->drive->chassis->moveDistance(19_in);
	// robot->lift->moveToPos(-30,30);

	// // re-position and get cube near barrier
	// robot->drive->chassis->moveDistance(-15_in);
	// robot->drive->turnToAngle(-105_deg, 200, HIGH_PRECISION);

	// robot->drive->chassisPID->setGains(
	// 	{0.00028, 0.00008, 0.0000003},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0} // Angle controller gains (helps drive straight)
	// );

	// robot->drive->chassis->moveDistance(23_in);
	// robot->lift->moveToPos(-30,30);


	// robot->runIntake(0);

	//Back up
	// robot->drive->chassis->getModel()->forward(-50);
	// pros::delay(2000);
	// robot->drive->chassis->getModel()->stop();


	// #ifdef RED
	// robot-> drive->moveLeft(50);
	// pros::delay(1500);
	// robot-> drive->moveLeft(0);
	// #else
	// // the blue case
	// robot-> drive->moveRight(50);
	// pros::delay(1500);
	// robot-> drive->moveRight(0);
	// #endif

	// robot->drive->chassis->moveDistance(30_in);

	// robot->drive->chassis->getModel()->forward(30);
	// pros::delay(2000);
	// robot->drive->chassis->getModel()->stop();


	//Staccking!!!
	// robot->drive->chassisPID->setGains(
	// 	{0.00022, 0.00011, 0.00000038},
	// 	{0.0006, 0.00003, 0.00000001},
	// 	{0.0005, 0, 0.000} // Angle controller gains (helps drive straight)
	// );
	// robot->runIntake(-80);
	// pros::delay(500);
	// robot->runIntake(0);

	// pros::delay(111);
	// robot->runIntake(30);

	// pros::delay(200);
	// robot->runIntake(0);

	// robot->runIntake(-25);
	// robot->tilter->fourbarGain = 0.18;
	// for(int i = 0; i < 20; i++){
	// 		if(i == 7){
	// 				robot->runIntake(0);
	// 		}
	// 		robot->tilter->moveFourbar(100);
	// 		pros::delay(100);
	// }
	// robot->tilter->fourbarGain = 0.18;


	// pros::delay(111);

	// robot->runIntake(-200);
	// pros::delay(100);
	// robot->runIntake(0);
	// robot->tilter->moveFourbar(-80);

	// pros::delay(300);
	// robot->runIntake(-200);
	// robot->drive->chassis->moveDistance(-20_in);

}
