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
            jittered_x = x + x_offset * inverted_samples;
            jittered_y = y + y_offset * inverted_samples;
            ray = computeRay(jittered_x, jittered_y);
            c = RayTracer::trace(ray);
            colors.push_back(c);
        }
    }

    return rt_lib::average(colors);
}
