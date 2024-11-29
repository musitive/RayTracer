#include "ReflectionIntersect.h"
#include "RayTracer.h"

ReflectionIntersect::ReflectionIntersect(AbstractObject* o, const Ray& r, const Point3D& p) : AbstractIntersect(o, r, p) {}

Colord ReflectionIntersect::computeColor(const Light& light, const int& depth) const {
    double dt = dot(ray.direction, normal);
    Direction reflection_direction = normal * (dt * 2) - ray.direction;
    Ray reflection(point, -reflection_direction);

    Colord cd = obj->getMaterial()->computeColor(this, light, false);
    Colord ct = RayTracer::trace(reflection, obj, depth+1);

    return ct * cd;
}