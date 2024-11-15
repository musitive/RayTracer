#include "Camera.h"
#include <numeric>
#include <random>

using namespace std;

double calculateAngle(double fov) {
    double angle_in_radians = M_PI * 0.5 * fov;
    return tan(angle_in_radians / 180.);
}