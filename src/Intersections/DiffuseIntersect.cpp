#include "DiffuseIntersect.h"
#include "Scene.h"

Absorption::Absorption(AbstractObject* o, const Ray& r, const vec3& p) : AbstractIntersect(o, r, p) {}

RGBColor Absorption::computeColor(const Light& light, const int& depth) const {
    bool blocked = isBlocked(light.position);
    return obj->computeColor(this, light, blocked);
}