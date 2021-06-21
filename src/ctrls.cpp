#include "main.h"
#include "globals.hpp"

int CurveFilter(int exponent, int x) {
    return std::pow(x, exponent) / std::pow(x,exponent-1);
}

void DriveTrain() {
    
}