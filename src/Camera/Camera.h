#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include <random>
#include "Vec.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Frame.h"

using namespace std;

class Camera {
    public:
        Camera(const int& width, const int& height, const Point3D& at, const Point3D& from,
                const Point3D& up, const double& fov, Environment* env);

        Frame render();
        int getWidth() const;
        int getHeight() const;

    private:
        int width, height;
        double aspect_ratio, angle;
        Point3D at, from, up;
        RayTracer* rt;

        double calculateAngle(double fov);
        Ray computeRay(double i, double j);
};

#endif