#ifndef JITTERTRACER_H
#define JITTERTRACER_H

#include "RayTracer.h"

class JitterTracer : public RayTracer {
    public:
        Colori trace(Ray ray, Environment* env, Object* current, const int& depth) override;
        double jitter(int i, double scale);
        Ray jitter(Ray r);
        vector<Colori> subdivide(int i, int j, double scale, double angle, double aspectratio, Environment* env);
};

#endif