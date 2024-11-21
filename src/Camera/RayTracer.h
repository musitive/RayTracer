#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "AbstractObject.h"
#include "Ray.h"
#include "Intersection.h"
#include "Environment.h"
#include <numeric>
#include <random>

// Forward declaration
class Scene;

class RayTracer {
    public:
        RayTracer();
        void setEnvironment(Environment* env);
        virtual Colord trace(const Ray& ray, AbstractObject* current, const int& depth);

    private:
        const int MAX_DEPTH = 2;
        Environment* env;
        Colord calculateReflection(const Intersection& closest_intersection, const int& depth);
        Colord calculateDiffuse(const Intersection& closest_intersection);
        Intersection findClosestIntersection(const Ray& ray, AbstractObject* current);
        bool isObjectBlocked(const Intersection& i, const Point3D& light_position);
};

#endif