#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include <random>
#include "Vec.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Frame.h"

class Scene;

class Camera {
    public:
        Camera(const int& width, const int& height, const Point3D& at, const Point3D& from,
                const Point3D& up, const double& fov);
        virtual ~Camera();

        Frame* render();
        int getWidth() const;
        int getHeight() const;

    protected:
        RayTracer* rt;
        Ray computeRay(double i, double j);

    private:
        int width, height;
        double aspect_ratio, angle;
        Point3D at, from, up;

        double calculateAngle(double fov);
        virtual Colord computerColorAtPixel(int i, int j);
};

#endif