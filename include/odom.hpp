#ifndef ODOM_HPP
#define ODOM_HPP

#define WHEEL_TO_MOTOR_RATIO 1
#define PI 3.1416
#define DRIVE_WHEEL_RADIUS 3.25
#define RAD_TO_DEG 57.2957
const float DIST_LEFT_WHEEL = 7.0f;
const float DIST_RIGHT_WHEEL = 7.0f;

void TrackOdom(void *param);
float DistToDeg(float x, bool reverse);
//An auto function, to follow a path to coords based on odom
void Rotation(float leftDist, float rigtDist);
void turn(float degrees);

#endif