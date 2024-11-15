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
        double width, height, aspect_ratio, angle;
        Position at, from, up;

    public:
        Camera(const double& width, const double& height, const Position& at, const Position& from, const Position& up, const double& fov) {
            this->width = width;
            this->height = height;
            this->at = at;
            this->from = from;
            this->up = up;
            angle = calculateAngle(fov);
            aspect_ratio = width / height;
        }

        double getWidth() {
            return width;
        }

        double getHeight() {
            return height;
        }

        Ray computeRay(double i, double j);
};

#endif