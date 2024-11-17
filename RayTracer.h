#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "Object.h"
#include "Ray.h"
#include "Environment.h"
#include <numeric>
#include <random>

using namespace std;

struct Intersection {
    Object* closest;
    Position p;
};

class RayTracer {
    public:
        virtual Colord trace(const Ray& ray, Environment* env, Object* current, const int& depth);

    private:
        const int MAX_DEPTH = 2;
        Colord calculateReflection(const Ray& ray, Intersection closest_intersection, Environment* env, const int& depth);
        Intersection findClosestIntersection(const Ray& ray, Environment* env, Object* current);
};

#endif