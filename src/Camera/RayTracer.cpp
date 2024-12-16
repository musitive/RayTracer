#include "RayTracer.h"
#include "Scene.h"
#include "MissedIntersect.h"
#include "ReflectionIntersect.h"
#include "DiffuseIntersect.h"
#include "KDTree.h"

KDTree* RayTracer::kdTree = nullptr;

RGBColor RayTracer::trace(const Ray& ray, AbstractObject* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return RGBColor(MAX_COLOR);
    Light light = Scene::getInstance()->getLight();

    void* closest_buffer = malloc(sizeof(Reflection));

    AbstractIntersection* i = findClosestIntersection(ray, reflected_object, closest_buffer);
    RGBColor c = i->computeColor(light, depth);

    free(closest_buffer);

    return c;
}

AbstractIntersection* RayTracer::findClosestIntersection(const Ray& ray, AbstractObject* reflected_object, void* closest_buffer) {
    void* buffer = malloc(sizeof(Reflection));

    AbstractIntersection* closest = new (closest_buffer) Miss(nullptr, Ray());
    closest = kdTree->findClosestIntersection(ray, reflected_object, closest_buffer, kdTree->root, closest, buffer);

    free(buffer);
    return closest;
}