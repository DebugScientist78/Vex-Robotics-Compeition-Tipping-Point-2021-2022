#include "main.h"
#include "globals.hpp"

#define SLEW_INCREMENT 30

int SignOf(int x) {
    if (x > 0) return 1;
    else if (x < 0) return -1;
    else return 0;
}

int CurveFilter(int exponent, int x) {
    return std::pow(x, exponent) / std::pow(x,exponent-1);
}

//Slew Rate, forces motors to increment to a desired value rather than instantly, intended to reduce current draw
void SlewRateTsk(void *param) {
    using namespace std;
    while (1) {
    if (driveFlag.load() == 1) {
        for (int i = 0; i < 4; i++) {
            if (abs(motorReq[i]) > abs(motorSent[i])) {
                motorSent[i] += SLEW_INCREMENT * SignOf(motorReq[i]);
                if (abs(motorSent[i]) > abs(motorReq[i])) motorSent[i] = motorReq[i];
            } else if (abs(motorReq[i]) < abs(motorSent[i])) {
                if (abs(motorSent[i]) < SLEW_INCREMENT) { 
                    motorSent[i] = 0;
                } else {
                    motorSent[i] -= SLEW_INCREMENT * SignOf(motorReq[i]);
                    if (SignOf(motorReq[i]) == 0) motorSent[i] -= SLEW_INCREMENT * SignOf(motorSent[i]);
                }
            }
            if (abs(motorSent[i] - motorReq[i]) < SLEW_INCREMENT) motorSent[i] = motorReq[i];
            pros::delay(15);
        }
    }
        pros::delay(15);
    }
}

void chainBarTsk(void *param) {
    //manual controls
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == 1) {

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == 1) {

    } else {
        
    }
}