#ifndef CTRLS_HPP
#define CTRLS_HPP

#define DEADZONE 35

int SignOf(int x);
int CurveFilter(int exponent, int x);
void SlewRateTsk(void *param);
void chainBarTsk(void *param);

#endif