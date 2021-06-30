#include "main.h"

float DistToDeg(float x, bool reverse) {
    if (!reverse) {
        return (x*180)/(PI*DRIVE_WHEEL_RADIUS);
    } else {
        return (x/360)*(2*PI*DRIVE_WHEEL_RADIUS);
    }
}

void TrackOdom(void *param) {
    float rWheel = 0; 
    float lWheel = 0; 
    float rWheelPrev = 0;
    float lWheelPrev = 0;
    float rDelta = 0;
    float lDelta = 0;
    float newDeg = 0;
    float prevDirection = 0;

    using namespace std;
    while (1) {
        rWheel = DistToDeg(dr1R.get_position(), true);
        lWheel = DistToDeg(dr1L.get_position()*-1, true);
        rDelta = rWheel - rWheelPrev;
        lDelta = lWheel - lWheelPrev;

        newDeg = (lDelta - rDelta) / (DIST_LEFT_WHEEL + DIST_RIGHT_WHEEL);
        degDirection += newDeg * -RAD_TO_DEG;
        if (degDirection >= 360) {
            float diff = degDirection - 360;
            degDirection = diff;
        }
        if (abs(newDeg) <= 0.001) {
            float straightAvg = (rWheel + lWheel) /2.0f;
            xOdom += straightAvg * cos(degDirection/RAD_TO_DEG);
            yOdom += straightAvg * sin(degDirection/RAD_TO_DEG);
        } else {
            if (abs(lDelta) != abs(rDelta) && (lDelta > 0 && rDelta > 0)) {
                float radius;
                float h;
                if (rDelta > lDelta) {
                    radius =  (lDelta)/(newDeg);
                    radius += DIST_LEFT_WHEEL;
                } else {
                    radius =  (rDelta)/(newDeg);
                    radius += DIST_RIGHT_WHEEL;
                }
                //tan(newDeg/2)=h/2/r
                //shortLen = (newDeg/360)*2PIr
                h = 2*(sin(newDeg/2)*radius);
                float otherAng = 1.5708f - (newDeg/2.0f);
                if (prevDirection == 90 || prevDirection == 270) {
                    if (lDelta > rDelta) xOdom += h*sin(otherAng);
                    else xOdom -= h*sin(otherAng);
                    yOdom += h*cos(otherAng);
                } else if (prevDirection == 0 || prevDirection == 180) {
                    yOdom -= h*cos(otherAng);
                    if (lDelta > rDelta) xOdom -= h*sin(otherAng);
                    else xOdom += h*sin(otherAng);
                }
                float xLocalDisp;
                float yLocalDisp;
                //if the bot turns towards the horizontal, then the vertical sides take the difference
                //otherwise the horizontal sides take the difference
                if (degDirection > 0 && degDirection < 90) {
                    if ((newDeg*-1) > 0) {

                    } else {

                    }
                }
            }
        }

        rWheelPrev = rWheel;
        lWheelPrev = lWheel;
        prevDirection = degDirection;
        pros::delay(20);
    }
} 

//relative motion. not to be used in odom tracking
//negative values would rotate the bot right, as the degree system follows polar coords
void turn(float degrees) {
    float rad = degrees/RAD_TO_DEG;
    const float TURN_VEL = 70;
    float dist;
    float currentDist;
    if (degrees > 0) {
        dist = rad * DIST_LEFT_WHEEL;
        dist = DistToDeg(dist,false);

        dr1L.move_relative(-dist,-TURN_VEL);
        dr1R.move_relative(-dist,-TURN_VEL);
        dr2L.move_relative(-dist,-TURN_VEL);
        dr2R.move_relative(-dist,-TURN_VEL);
        pros::delay(2000);
    } else {
        dist = rad * DIST_RIGHT_WHEEL;
        dist = DistToDeg(dist,false);

        dr1L.move_relative(dist,TURN_VEL);
        dr1R.move_relative(dist,TURN_VEL);
        dr2L.move_relative(dist,TURN_VEL);
        dr2R.move_relative(dist,TURN_VEL);
        pros::delay(2000);
    }
}