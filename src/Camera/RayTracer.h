#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "Vec.h"
#include "AbstractObject.h"
#include "Ray.h"
#include "AbstractIntersect.h"
#include "KDTree.h"
#include <numeric>
#include <random>

/**
 * @class RayTracer
 * @brief The RayTracer class is a static class that contains the logic for casting rays and tracing them through the
 * scene. I opted to store this logic in it's own class so that it can easily be replaced or extended in the future.
 */
class RayTracer {
    public:
        static KDTree *kd_tree;

        // This method traces a ray through the scene and returns the color of the object it intersects.
        static RGBColor trace(const Ray &ray, AbstractObject *current = nullptr, const int &depth = 0);

        // Determines if an object is blocked from a light source by another object
        static bool isObjectBlocked(const vec3 &light_position, const vec3 &hit_point, const AbstractObject *current);

    private:
        static const int MAX_DEPTH = 3;     // Maximum depth of recursion, should be set in the SceneBuilder

        // This method finds the closest intersection of a ray with an object in the scene, using a KD tree to
        // reduce the number of intersection tests in more complex scenes.
        static void findClosestIntersection(const Ray &ray, AbstractObject *reflected_object,
            void *closest_buffer);
};

#endif