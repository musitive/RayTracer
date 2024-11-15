#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include <random>
#include "Vec.h"
#include "Ray.h"

using namespace std;

class Camera {
    private:
        

    public:
        double width, height;
        Position at;
        Position from;
        Position up;
        double fov;

        Camera() {
            at = Position();
            from = Position();
            up = Position();
            fov = 0;
        }
        Camera(const double& width, const double& height, const Position& at, const Position& from, const Position& up, const double& fov) :
            width(width), height(height), at(at), from(from), up(up), fov(fov) {}
};

double calculateAngle(double fov);

#endif