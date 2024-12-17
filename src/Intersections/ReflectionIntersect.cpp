#include "ReflectionIntersect.h"
#include "RayTracer.h"

Reflection::Reflection(AbstractObject* o, const Ray& r, const vec3& p) : AbstractIntersect(o, r, p) {}

RGBColor Reflection::computeColor(const Light& light, const int& depth) const {
    double dt = dot(ray.direction, normal);
    Direction reflect_dir = normal * (dt * 2) - ray.direction;
    Ray reflection(hit_point, -reflect_dir);

    RGBColor cd = obj->computeColor(this, light);
    RGBColor ct = RayTracer::trace(reflection, obj, depth+1);

    return ct * cd;
}