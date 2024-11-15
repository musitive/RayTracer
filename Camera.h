#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include <random>
#include "Vec.h"
#include "Ray.h"

using namespace std;

double calculateAngle(double fov);

class Camera {
    private:
        double angle;
        double aspect_ratio;

    public:
        double width, height;
        Position at;
        Position from;
        Position up;
        double fov;

        Camera(const double& width, const double& height, const Position& at, const Position& from, const Position& up, const double& fov) {
            this->width = width;
            this->height = height;
            this->at = at;
            this->from = from;
            this->up = up;
            this->fov = fov;
            angle = calculateAngle(fov);
            aspect_ratio = width / height;
        }

        Ray computeRay(double i, double j);
};

#endif