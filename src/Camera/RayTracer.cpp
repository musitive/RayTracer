#include "RayTracer.h"
#include "Scene.h"
#include "Intersection.h"

Environment* RayTracer::env = nullptr;

void RayTracer::setEnvironment(Environment* env) {
    RayTracer::env = env;
}

Colord RayTracer::trace(const Ray& ray, AbstractObject* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return Colord(1);
    
    AbstractIntersect* i = findClosestIntersection(ray, reflected_object);
    Colord c = i->computeColor(env->light, depth);
    free(i);

    return c;
}

RayTracer::AbstractIntersect* RayTracer::findClosestIntersection(const Ray& ray, AbstractObject* reflected_object) {
    AbstractIntersect* closest = IntersectionFactory::createMissed();
    AbstractIntersect* next;

    for(AbstractObject* o: env->env) {
        if (o == reflected_object) continue;

        next = IntersectionFactory::create(o, ray);
        if (next->isCloserThan(closest)) closest = next;
    }

    return closest;
}

RayTracer::AbstractIntersect* RayTracer::IntersectionFactory::create(AbstractObject* o, const Ray& r) {
    AbstractIntersect* i;

    Point3D p = o->findIntersection(r);

    if (p == MISS) i = new MissedIntersect(o, r);
    else if (o->getMaterial()->isReflective)
        i = new ReflectionIntersect(o, r, p);
    else
        i = new DiffuseIntersect(o, r, p);

    return i;
}

RayTracer::AbstractIntersect* RayTracer::IntersectionFactory::createMissed() {
    return new MissedIntersect(nullptr, Ray());
}