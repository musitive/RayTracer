#include "ReflectionIntersect.h"
#include "RayTracer.h"

ReflectionIntersect::ReflectionIntersect(Actor* o, const Ray& r, const Point3D& p) : AbstractIntersect(o, r, p) {}

RGBColor ReflectionIntersect::computeColor(const Light& light, const int& depth) const {
    double dt = dot(ray.direction, normal);
    Direction reflection_direction = normal * (dt * 2) - ray.direction;
    Ray reflection(point, -reflection_direction);

    RGBColor cd = obj->getMaterial()->computeColor(this, light, false);
    RGBColor ct = RayTracer::trace(reflection, obj, depth+1);

    return ct * cd;
}