#include "RayTracer.h"
#include "Scene.h"
#include "Intersection.h"

Environment* RayTracer::env = nullptr;

void RayTracer::setEnvironment(Environment* env) {
    RayTracer::env = env;
}

Colord RayTracer::trace(const Ray& ray, AbstractObject* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return Colord(MAX_COLOR);
    
    AbstractIntersect* i = findClosestIntersection(ray, reflected_object);
    Colord c = i->computeColor(env->light, depth);
    free(i);

    return c;
}

AbstractIntersect* RayTracer::findClosestIntersection(const Ray& ray, AbstractObject* reflected_object) {
    AbstractIntersect* closest = IntersectionFactory::createMissed();
    AbstractIntersect* next;

    for(AbstractObject* o: env->env) {
        if (o == reflected_object) continue;

        next = IntersectionFactory::create(o, ray);
        if (next->isCloserThan(closest)) closest = next;
    }

    return closest;
}

AbstractIntersect* RayTracer::IntersectionFactory::create(AbstractObject* obj, const Ray& ray) {
    AbstractIntersect* i;

    Point3D p = obj->findIntersection(ray);

    if (p == MISS) i = new MissedIntersect(obj, ray);
    else if (obj->getMaterial()->isReflective)
        i = new ReflectionIntersect(obj, ray, p);
    else
        i = new DiffuseIntersect(obj, ray, p);

    return i;
}

AbstractIntersect* RayTracer::IntersectionFactory::createMissed() {
    return new MissedIntersect(nullptr, Ray());
}