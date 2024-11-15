#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "Object.h"
#include "Ray.h"
#include "Environment.h"
#include <numeric>
#include <random>

using namespace std;

class RayTracer {
    private:
        const int MAX_DEPTH = 4;
        Colori calculateReflection(Ray ray, Position p, Object* closest, Environment* env, const int& depth);
    public:
        Ray computeRay(double i, double j, double angle, double aspectratio, Environment* env);
        virtual Colori trace(Ray ray, Environment* env, Object* current, const int& depth);
};

#endif