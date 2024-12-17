#include "IntersectionFactory.h"

AbstractIntersect* IntersectionFactory::create(AbstractObject* obj, const Ray& ray, void* buffer) {
    vec3 p = obj->findIntersection(ray);

    if (p == MISS)
        return new (buffer) Miss(obj, ray);
    else if (obj->isReflective())
        return new (buffer) Reflection(obj, ray, p);
    else
        return new (buffer) Absorption(obj, ray, p);
}

AbstractIntersect* IntersectionFactory::createMissed(void* buffer) {
    return new (buffer) Miss();
}