#include "Drive.hpp"
#include "SheBelieved.hpp"
#include "menu/Menu.hpp"

Drive::Drive()
{
    MotorGroup left({
					 Motor(DRIVE_LEFT_FRONT, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_MID, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					 Motor(DRIVE_LEFT_BACK, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
	MotorGroup right({
					  Motor(DRIVE_RIGHT_FRONT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_MID, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees),
					  Motor(DRIVE_RIGHT_BACK, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees)});
    leftMotors = std::make_shared<MotorGroup>(left);
    rightMotors = std::make_shared<MotorGroup>(right);
    leftMotors->setBrakeMode(AbstractMotor::brakeMode::coast);
    rightMotors->setBrakeMode(AbstractMotor::brakeMode::coast);

    // save ports in a vector
    leftMotorPorts.reserve(3);
    leftMotorPorts.push_back(std::make_tuple(DRIVE_LEFT_FRONT, -1));
    leftMotorPorts.push_back(std::make_tuple(DRIVE_LEFT_MID, 1));
    leftMotorPorts.push_back(std::make_tuple(DRIVE_LEFT_BACK, -1));
    rightMotorPorts.reserve(3);
    rightMotorPorts.push_back(std::make_tuple(DRIVE_RIGHT_FRONT, 1));
    rightMotorPorts.push_back(std::make_tuple(DRIVE_RIGHT_MID, -1));
    rightMotorPorts.push_back(std::make_tuple(DRIVE_RIGHT_BACK, 1));

    leftEncoder = std::make_shared<ADIEncoder>(ENCODER_LEFT_DRIVE_TOP, ENCODER_LEFT_DRIVE_BOT, false);
    rightEncoder = std::make_shared<ADIEncoder>(ENCODER_RIGHT_DRIVE_TOP, ENCODER_RIGHT_DRIVE_BOT, false);

    std::shared_ptr<okapi::OdomChassisController> c = ChassisControllerBuilder()
                .withMotors(leftMotors, rightMotors)
                .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 4.5_in},1024})
                .withGains(
                    //{0.00006, 0.00000000001, 0.000000000000001}, // Distance controller gains
                    {0.00022, 0.00011, 0.00000038},
                    {0.0006, 0.000003, 0.000},
                    {0.0005, 0, 0}
                    // {0.003, 0, 0.000}, // turn controller gains
                    // {0.0005, 0, 0.00000}  // angle controller gains (helps drive straight)
                )
                .withSensors(leftEncoder, rightEncoder)
                .withClosedLoopControllerTimeUtil(50, 5, 100_ms)
                .withOdometry({{3.25_in, 5_in},1024}, StateMode::CARTESIAN, 0_mm, 0_deg)
                .buildOdometry();
    chassis = std::dynamic_pointer_cast<okapi::DefaultOdomChassisController>(c);
    chassisPID = std::dynamic_pointer_cast<okapi::ChassisControllerPID>(chassis->getChassisController());
}

void Drive::opControl(pros::Controller& joystick) {
    double forward = joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
    double turn = joystick.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
    // this->chassis->getModel()->arcade(forward, turn);

    // forward = std::clamp(forward, -1.0, 1.0);
    // turn = std::clamp(turn, -1.0, 1.0);
    // double leftOutput = 0;
    // double rightOutput = 0;
    // double max = std::copysign(std::max(std::abs(forward), std::abs(turn)), forward);
    // double MAX_VELOCITY = 200;
    // double MAX_VOLTAGE = 12000;

    // if(forward >= 0.0) {
    //     if(turn >= 0.0) {
    //         leftOutput = max;
    //         rightOutput = forward - turn * 0.7;
    //     } else {
    //         leftOutput = forward + turn * 0.7;
    //         rightOutput = max;
    //     }
    // } else {
    //     if(turn >= 0.0) {
    //         leftOutput = forward + turn * 0.7;
    //         rightOutput = max;
    //     } else {
    //         leftOutput = max;
    //         rightOutput = forward - turn * 0.7;
    //     }
    // }

    // leftOutput = std::clamp(leftOutput, -1.0, 1.0);
    // rightOutput = std::clamp(rightOutput, -1.0, 1.0);
    // leftMotors->moveVoltage((forward + turn) * MAX_VOLTAGE);
    // rightMotors->moveVoltage((forward - turn) * MAX_VOLTAGE);
    // leftMotors->moveVoltage(leftOutput * MAX_VOLTAGE);
    // rightMotors->moveVoltage(rightOutput * MAX_VOLTAGE);
    this->moveLeft((forward + turn * 0.7) * 127);
    this->moveRight((forward - turn * 0.7) * 127);
    // this->moveLeft(leftOutput * 200);
    // this->moveRight(rightOutput * 200);
}

void Drive::moveLeft(int power) {
    for (std::tuple<int16_t, int16_t> port : leftMotorPorts) {
        auto [portnum, direction] = port;
        pros::c::motor_move(portnum, power * direction);
    }
}

void Drive::moveRight(int power) {
    for (std::tuple<int16_t, int16_t> port : rightMotorPorts) {
        auto [portnum, direction] = port;
        pros::c::motor_move(portnum, power * direction);
    }
}

void Drive::turnToAngle(QAngle angle, int vel, DrivePrecision precision){
    int turnsModifier = turnsMirrored ? -1 : 1;
    // update desired position
    t_d = angle;
    switch(precision) {
        case HIGH_PRECISION:
            this->chassis->getModel()->setMaxVelocity(vel);
            this->chassis->turnToAngle(turnsModifier * t_d);
            break;
        case MEDIUM_PRECISION:
            break;
        case NO_PRECISION:
            QAngle t_e = t_d;
            while(!chassisPID->isSettled() && t_e.abs().convert(degree) > degree * NO_PRECISION_TURN_THRESH) {
                this->chassis->turnAngleAsync(t_e * turnsModifier);
                OdomState cur_state = chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
                t_e = t_d - cur_state.theta;
                pros::delay(10);
            }
            this->chassis->stop();
            break;
    }
}

void Drive::driveDist(QLength len, int vel, DrivePrecision precision){
    // Update desired position
    float x_od = sin(t_d.convert(radian)); // x orientation
    float y_od = cos(t_d.convert(radian)); // y orientation
    x_d = x_d + (len * x_od); // Update desired x
    y_d = y_d + (len * y_od); // Update desired y
    Menu::getMenu()->addDebugPrint(3, "x_d:" + std::to_string(x_d.convert(inch))+ " y_d:" + std::to_string(y_d.convert(inch)));
    switch(precision) {
        case HIGH_PRECISION:
            this->chassis->getModel()->setMaxVelocity(vel);
            this->chassis->moveDistance(len);
            break;
        case MEDIUM_PRECISION:
            break;
        case NO_PRECISION:
            QLength e_o = getOrientedError();
            break;
    }

    this->chassis->getModel()->setMaxVelocity(vel);
    this->chassis->moveDistance(e_o);
}

QLength Drive::getOrientedError() {
    // Get orientation error
    OdomState cur_state = chassis->getOdometry()->getState(okapi::StateMode::CARTESIAN);
    QLength x_e = x_d - cur_state.x; // x error
    QLength y_e = y_d - cur_state.y; // y error
    QAngle t_e = t_d - cur_state.theta; // theta error
    float x_o = sin(cur_state.theta.convert(radian)); // x orientation
    float y_o = cos(cur_state.theta.convert(radian)); // y orientation

    QLength e_o = (x_o * x_e) + (y_o * y_e); // calc oriented error
    return e_o;
}

void Drive::setTurnsMirrored(bool mirror) {
    this->turnsMirrored = mirror;   
}