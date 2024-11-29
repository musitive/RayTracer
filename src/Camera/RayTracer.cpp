#include "RayTracer.h"
#include "Scene.h"
#include "Intersection.h"

Colord RayTracer::trace(const Ray& ray, AbstractObject* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return Colord(MAX_COLOR);
    Light light = Scene::getInstance()->getLight();

    void* closest_buffer = malloc(sizeof(ReflectionIntersect));
    AbstractIntersect* i = findClosestIntersection(ray, reflected_object, closest_buffer);
    Colord c = i->computeColor(light, depth);

    return c;
}

AbstractIntersect* RayTracer::findClosestIntersection(const Ray& ray, AbstractObject* reflected_object, void* closest_buffer) {
    void* buffer = malloc(sizeof(ReflectionIntersect));
    vector<AbstractObject*> actors = Scene::getInstance()->getActors();
    AbstractIntersect* closest = new (closest_buffer) MissedIntersect(nullptr, Ray());
    AbstractIntersect* next;

    for (AbstractObject* o : actors) {
        if (o == reflected_object) continue;

        next = IntersectionFactory::create(o, ray, buffer);
        if (next->isCloserThan(closest))
            memcpy(closest_buffer, buffer, sizeof(ReflectionIntersect));
    }
    free(buffer);

    return closest;
}

AbstractIntersect* RayTracer::IntersectionFactory::create(AbstractObject* obj, const Ray& ray, void* buffer) {
    Point3D p = obj->findIntersection(ray);

    if (p == MISS)
        return new (buffer) MissedIntersect(obj, ray);
    else if (obj->getMaterial()->isReflective)
        return new (buffer) ReflectionIntersect(obj, ray, p);
    else
        return new (buffer) DiffuseIntersect(obj, ray, p);
}

AbstractIntersect* RayTracer::IntersectionFactory::createMissed(void* buffer) {
    return new (buffer) MissedIntersect(nullptr, Ray());
}