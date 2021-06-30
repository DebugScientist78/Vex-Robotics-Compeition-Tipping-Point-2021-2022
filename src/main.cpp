#include "main.h"

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

	dr1L.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	dr2L.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	dr1R.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	dr2R.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

	dr1L.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	dr1R.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

	pros::Task driveTsk(SlewRateTsk);
	pros::Task odomTsk(TrackOdom);
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
	yOdom = 105.7f;
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
void opcontrol() {
    int y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	using namespace std;
	int local_motorSent[4];
	while (true) {
    	y = CurveFilter(3,y);
		//Prevents the slew Task from running, ensures a race condition never occurs
		driveFlag = 0;
		if (abs(y) > DEADZONE) {
			motorReq[dr1L_PORT-1] = y;
			motorReq[dr2L_PORT-1] = y;
			motorReq[dr1R_PORT-1] = -y;
			motorReq[dr2R_PORT-1] = -y;
		} else {
			motorReq[dr1L_PORT-1] = 0;
			motorReq[dr2L_PORT-1] = 0;
			motorReq[dr1R_PORT-1] = 0;
			motorReq[dr2R_PORT-1] = 0;
		}
		//As the task is closed, copy their values to local array for motor assignemnt, ensures after the task opens, a race condition won't happen
		local_motorSent[dr1L_PORT-1] = motorSent[dr1L_PORT-1];
		local_motorSent[dr2L_PORT-1] = motorSent[dr2L_PORT-1];
		local_motorSent[dr1R_PORT-1] = motorSent[dr1R_PORT-1];
		local_motorSent[dr1R_PORT-1] = motorSent[dr1R_PORT-1];

		//Opens slew task
		driveFlag = 1;

		//Applies sent motor values to the motors
		dr1L.move(local_motorSent[dr1L_PORT-1]);
		dr2L.move(local_motorSent[dr2L_PORT-1]);
		dr1R.move(local_motorSent[dr1R_PORT-1]);
		dr2R.move(local_motorSent[dr2R_PORT-1]);

		pros::delay(20);
	}
}
