#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "AbstractObject.h"
#include "Ray.h"
#include "Environment.h"
#include <numeric>
#include <random>

class RayTracer {
    public:
        static void setEnvironment(Environment* env);
        static Colord trace(const Ray& ray, AbstractObject* current, const int& depth);

        class AIntersect; // Forward declaration
        class MissedIntersection; // Forward declaration
        class ReflectionIntersect; // Forward declaration
        class DiffuseIntersect; // Forward declaration

    private:
        static const int MAX_DEPTH = 2;
        static Environment* env;

        static AIntersect* findClosestIntersection(const Ray& ray, AbstractObject* current);

        class IntersectionFactory {
            public:
                static AIntersect* create(AbstractObject* o, const Ray& r);
                static AIntersect* createMissed();
        };
};

#endif