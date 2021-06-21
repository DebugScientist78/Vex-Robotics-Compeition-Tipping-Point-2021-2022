#include "main.h"
#define dr1L_PORT 1
#define dr2L_PORT 2
#define dr1R_PORT 3
#define dr2R_PORT 4

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

pros::Motor dr1L(dr1L_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor dr2L(dr2L_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor dr1R(dr1R_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor dr2R(dr2R_PORT, pros::E_MOTOR_GEARSET_18, false);