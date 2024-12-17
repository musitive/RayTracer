#include "AntiAliasCam.h"

#include <random>
#include <vector>
#include <cmath>

// Overrides the base class color computation method to add anti-aliasing
RGBColor AntiAliasCam::computeColorAtPixel(const int &x, const int &y) {
    std::vector<RGBColor> colors = std::vector<RGBColor>();
    double jittered_x, jittered_y;
    Ray ray;
    RGBColor c;

    // Cast multiple rays per pixel and average the colors
    for(int y_offset = 0; y_offset < samples; ++y_offset) {
        for(int x_offset = 0; x_offset < samples; ++x_offset) {
            jittered_x = jitter(x) + x_offset * inverted_samples;
            jittered_y = jitter(y) + y_offset * inverted_samples;
            ray = computeRay(jittered_x, jittered_y);
            c = RayTracer::trace(ray);
            colors.push_back(c);
        }
    }

    return rt_lib::average(colors);
}

// Adds a random offset to the pixel coordinates to reduce aliasing
double AntiAliasCam::jitter(const int &x) const {
    std::random_device rd;  // obtain a random number from hardware
    std::default_random_engine re(rd());  // random number generator
    std::uniform_real_distribution<double> unif(0, inverted_samples);   // uniform distribution
    return x + unif(re);
}
