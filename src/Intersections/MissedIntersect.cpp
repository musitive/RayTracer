#include "MissedIntersect.h"
#include "Scene.h"

Miss::Miss(AbstractObject* o, const Ray& r)
    : AbstractIntersection(o, r, MISS, INF, Point3D(0)) {}

RGBColor Miss::computeColor(const Light& light, const int& depth) const {
    return Scene::getInstance()->getGlobalIllumination();
}