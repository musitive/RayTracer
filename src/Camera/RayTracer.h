#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "AbstractObject.h"
#include "Ray.h"
#include "AbstractIntersect.h"
#include <numeric>
#include <random>

class RayTracer {
    public:
        static RGBColor trace(const Ray& ray, Actor* current = nullptr, const int& depth = 0);

    private:
        static const int MAX_DEPTH = 2;

        static AbstractIntersect* findClosestIntersection(const Ray& ray, Actor* current, void* closest_buffer);
};

class IntersectionFactory {
    public:
        static AbstractIntersect* create(Actor* obj, const Ray& ray, void* buffer);
        static AbstractIntersect* createMissed(void* buffer);
};

#endif