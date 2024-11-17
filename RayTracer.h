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
    public:
        virtual Colord trace(const Ray& ray, Environment* env, Object* current, const int& depth);

    private:
        const int MAX_DEPTH = 2;
        Colord calculateReflection(const Ray& ray, Position p, Object* closest, Environment* env, const int& depth);
};

#endif