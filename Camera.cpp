#include "Camera.h"
#include <numeric>
#include <random>

using namespace std;

Ray Camera::computeRay(double i, double j) {
    double xx = (2 * (i * 1 / width) - 1) * angle * aspect_ratio;
    double yy = (1 - 2 * (j * 1 / height)) * angle;
    Position look_at = Position(xx,yy,0) + at;

    Ray ray = Ray(from, look_at);
    return ray;
}

double calculateAngle(double fov) {
    double angle_in_radians = M_PI * 0.5 * fov;
    return tan(angle_in_radians / 180.);
}