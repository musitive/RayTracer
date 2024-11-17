#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "Object.h"
#include "Ray.h"
#include "Environment.h"
#include "Intersection.h"
#include <numeric>
#include <random>

using namespace std;

class RayTracer {
    public:
        RayTracer(Environment* env);
        virtual Colord trace(const Ray& ray, Object* current, const int& depth);

    private:
        const int MAX_DEPTH = 2;
        Environment* env;
        Colord calculateReflection(const Intersection& closest_intersection, const int& depth);
        Colord calculateDiffuse(const Intersection& closest_intersection);
        Intersection findClosestIntersection(const Ray& ray, Object* current);
        bool isObjectBlocked(const Intersection& i, const Position& light_position);
};

#endif