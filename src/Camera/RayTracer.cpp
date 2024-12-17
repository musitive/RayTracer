#include "RayTracer.h"
#include "Scene.h"
#include "MissedIntersect.h"
#include "ReflectionIntersect.h"
#include "DiffuseIntersect.h"
#include "KDTree.h"

KDTree* RayTracer::kd_tree = nullptr;

RGBColor RayTracer::trace(const Ray& ray, AbstractObject* current, const int& depth) {
    if (depth >= MAX_DEPTH) return MAX_COLOR;

    // Allocate memory for the closest intersection. This is done to avoid multiple allocations.
    // This information can't be stored on the stack since it needs to be used elsewhere. Since abstract
    // classes can't be return types in C++, I opted to use pointers to the Intersections.
    void *closest_buffer = malloc(sizeof(Reflection));
    IntersectionFactory::createMissed(closest_buffer);
    Light light = Scene::getInstance()->getLight();

    findClosestIntersection(ray, current, closest_buffer);
    RGBColor color = ((AbstractIntersect*) closest_buffer)->computeColor(light, depth);

    free(closest_buffer);
    return color;
}

bool RayTracer::isObjectBlocked(const vec3& light_position, const vec3& hit_point, const AbstractObject* current) {
    Ray shadow_ray(hit_point, light_position - hit_point);
    return kd_tree->isObjectBlocked(shadow_ray, current);
}

void RayTracer::findClosestIntersection(const Ray &ray, AbstractObject *reflected_object, void *closest_buffer)
{
    void *current_buffer = malloc(sizeof(Reflection));
    IntersectionFactory::createMissed(current_buffer);

    kd_tree->findClosestIntersection(ray, closest_buffer, current_buffer);

    free(current_buffer);
    return;
}