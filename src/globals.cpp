#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

pros::Motor dr1L(dr1L_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor dr2L(dr2L_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor dr1R(dr1R_PORT, pros::E_MOTOR_GEARSET_18, false);
pros::Motor dr2R(dr2R_PORT, pros::E_MOTOR_GEARSET_18, false);

int motorReq[4] = {0,0,0,0};
int motorSent[4] = {0,0,0,0};

std::atomic<int> driveFlag(0);

float xOdom = 0.0f;
float yOdom = 0.0f;
float degDirection = 0.0f;