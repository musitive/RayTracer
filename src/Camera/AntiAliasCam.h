#ifndef ANTI_ALIAS_CAM_H
#define ANTI_ALIAS_CAM_H

#include "Camera.h"

class AntiAliasCam : public Camera {
    protected:
        int samples;                // Number of samples to take per pixel, defined in the constructor
        double inverted_samples;    // 1 / samples for efficiency

        // Overrides the base class color computation method to add anti-aliasing
        RGBColor computeColorAtPixel(const int &x, const int &y) override;

        // Adds a random offset to the pixel coordinates to reduce aliasing
        double jitter(const int &x) const;
};

#endif