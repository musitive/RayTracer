#pragma once

#include "../Vec.h"

using namespace std;

class Camera {
    private:
        double width, height;
        Position at;
        Position from;
        Position up;
        double fov;

    public:
        Camera(double width, double height, Position at, Position from, Position up, double fov);

        double getWidth();
        double getHeight();
};
