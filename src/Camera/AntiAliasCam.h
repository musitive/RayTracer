#ifndef ANTI_ALIAS_CAM_H
#define ANTI_ALIAS_CAM_H

#include "Camera.h"

class AntiAliasCam : public Camera {
    public:
        AntiAliasCam(const double &width, const double &height, const vec3 &at, const vec3 &from, const vec3 &up, const double &fov, const int &samples)
            : Camera(width, height, at, from, up, fov), samples(samples), inverted_samples(1.0 / samples) {}

    protected:
        int samples;                // Number of samples to take per pixel, defined in the constructor
        double inverted_samples;    // 1 / samples for efficiency

        // Overrides the base class color computation method to add anti-aliasing
        RGBColor computeColorAtPixel(const int &x, const int &y) override;

        // Adds a random offset to the pixel coordinates to reduce aliasing
        double jitter(const int &x) const;
};

#endif