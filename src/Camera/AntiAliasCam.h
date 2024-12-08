#ifndef ANTI_ALIAS_CAM_H
#define ANTI_ALIAS_CAM_H

#include "Camera.h"

class AntiAliasCam : public Camera {
    public:
        AntiAliasCam(const int& width, const int& height, const Point3D& look_at, const Point3D& from,
                     const Point3D& up, const double& fov, const int& samples);

    private:
        int samples;

        RGBColor computeColorAtPixel(int i, int j) override;
        double jitter(int i, double scale);
        Ray jitter(Ray ray);
};

#endif