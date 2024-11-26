#include "AntiAliasCam.h"

double AntiAliasCam::jitter(int i, double scale) {
    uniform_real_distribution<double> unif(0, scale);
    default_random_engine re;
    return i + unif(re);
}

Ray AntiAliasCam::jitter(Ray ray) {
    uniform_real_distribution<double> unif(0,0.1);
    default_random_engine re;
    ray.direction = ray.direction + Vector3D(unif(re));
    return ray;
}

AntiAliasCam::AntiAliasCam(const int& width, const int& height, const Point3D& at, const Point3D& from,
                           const Point3D& up, const double& fov, const int& samples)
    : Camera(width, height, at, from, up, fov), samples(samples) {}

Colord AntiAliasCam::computerColorAtPixel(int i, int j) {
    vector<Colord> colors = vector<Colord>();
    double altered_i, altered_j;
    Ray r;
    Colord c;

    double scale = 1. / (double) samples;

    for(int y = 0; y < samples; ++y) {
        for(int x = 0; x < samples; ++x) {
            altered_i = jitter(i, scale) + x * scale;
            altered_j = jitter(j, scale) + y * scale;
            r = computeRay(altered_i, altered_j);
            c = rt->trace(r, nullptr, 0);
            colors.push_back(c);
        }
    }

    return average(colors);
}
