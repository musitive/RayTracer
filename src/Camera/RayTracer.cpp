#include "RayTracer.h"
#include "Scene.h"
#include "Intersection.h"

Environment* RayTracer::env = nullptr;

void RayTracer::setEnvironment(Environment* env) {
    RayTracer::env = env;
}

Colord RayTracer::trace(const Ray& ray, AbstractObject* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return Colord(1);
    
    AIntersect* i = findClosestIntersection(ray, reflected_object);

    return i->computeColor(env->light, env->ambient_light, depth);
}

RayTracer::AIntersect* RayTracer::findClosestIntersection(const Ray& ray, AbstractObject* reflected_object) {
    AIntersect* closest = IntersectionFactory::createMissed();
    AIntersect* next;

    for(AbstractObject* o: env->env) {
        if (o == reflected_object) continue;

        next = IntersectionFactory::create(o, ray);
        if (next->isCloserThan(closest)) closest = next;
    }

    return closest;
}

RayTracer::AIntersect* RayTracer::IntersectionFactory::create(AbstractObject* o, const Ray& r) {
    AIntersect* i;

    Point3D p = o->findIntersectPosition(r);

    if (p == MISS) i = new MissedIntersection(o, r);
    else if (o->getMaterial()->isReflective)
        i = new ReflectionIntersect(o, r, p);
    else
        i = new DiffuseIntersect(o, r, p);

    return i;
}

RayTracer::AIntersect* RayTracer::IntersectionFactory::createMissed() {
    return new MissedIntersection(nullptr, Ray(Point3D(0), Direction(0)));
}