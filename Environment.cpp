#include "Environment.h"

double calculateAngle(double fov) {
    double angle_in_radians = M_PI * 0.5 * fov;
    return tan(angle_in_radians / 180.);
}