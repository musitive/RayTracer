#include "RayTracer.h"
#include "Scene.h"
#include "MissedIntersect.h"
#include "ReflectionIntersect.h"
#include "DiffuseIntersect.h"

RGBColor RayTracer::trace(const Ray& ray, Actor* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return RGBColor(MAX_COLOR);
    Light light = Scene::getInstance()->getLight();

    void* closest_buffer = malloc(sizeof(Reflection));

    AbstractIntersection* i = findClosestIntersection(ray, reflected_object, closest_buffer);
    RGBColor c = i->computeColor(light, depth);

    free(closest_buffer);

    return c;
}

AbstractIntersection* RayTracer::findClosestIntersection(const Ray& ray, Actor* reflected_object, void* closest_buffer) {
    void* buffer = malloc(sizeof(Reflection));
    vector<Actor*> actors = Scene::getInstance()->getActors();
    AbstractIntersection* closest = new (closest_buffer) Miss(nullptr, Ray());
    AbstractIntersection* next;

    for (Actor* o : actors) {
        if (o == reflected_object) continue;

        next = IntersectionFactory::create(o, ray, buffer);
        if (next->isCloserThan(closest))
            memcpy(closest_buffer, buffer, sizeof(Reflection));
    }

    free(buffer);
    return closest;
}

AbstractIntersection* IntersectionFactory::create(Actor* obj, const Ray& ray, void* buffer) {
    Point3D p = obj->findIntersection(ray);

    if (p == MISS)
        return new (buffer) Miss(obj, ray);
    else if (obj->getMaterial()->isReflective)
        return new (buffer) Reflection(obj, ray, p);
    else
        return new (buffer) Absorption(obj, ray, p);
}

AbstractIntersection* IntersectionFactory::createMissed(void* buffer) {
    return new (buffer) Miss(nullptr, Ray());
}