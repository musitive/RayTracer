#pragma once

#include "RayTracer.h"

class JitterRayTracer : public RayTracer {
    private:
        int rays_per_pixel;

    public:
        JitterRayTracer(int rays_per_pixel);
        double jitter(int i, double scale);
        Ray jitter(Ray r);
        Ray computeRay(double i, double j, double angle, double aspectratio, Scene* env);
        virtual Colori trace(Ray ray, Scene* env, Object* current, const int& depth);
}