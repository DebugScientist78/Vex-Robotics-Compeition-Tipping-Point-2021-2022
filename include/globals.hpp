#ifndef GLOBALS_HPP
#define GLOBALS

#include <atomic>
#define dr1L_PORT 1
#define dr2L_PORT 2
#define dr1R_PORT 3
#define dr2R_PORT 4

extern pros::Controller master;
extern pros::Controller partner;

//Motors
//Grouped for differentials
//Drive
extern pros::Motor dr1L;
extern pros::Motor dr2L;
extern pros::Motor dr1R;
extern pros::Motor dr2R;
extern int motorReq[4];
extern int motorSent[4];
extern std::atomic<int> driveFlag;

extern float xOdom;
extern float yOdom;
extern float degDirection;

#endif