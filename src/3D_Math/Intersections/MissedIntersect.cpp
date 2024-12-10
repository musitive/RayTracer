#include "MissedIntersect.h"
#include "Scene.h"

MissedIntersect::MissedIntersect(Actor* o, const Ray& r)
    : AbstractIntersect(o, r, MISS, INF, Point3D(0)) {}

RGBColor MissedIntersect::computeColor(const Light& light, const int& depth) const {
    return Scene::getInstance()->getGlobalIllumination();
}