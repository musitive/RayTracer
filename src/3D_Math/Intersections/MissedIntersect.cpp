#include "MissedIntersect.h"
#include "Scene.h"

MissedIntersect::MissedIntersect(AbstractObject* o, const Ray& r)
    : AbstractIntersect(o, r, MISS, INF, Point3D(0)) {}

Colord MissedIntersect::computeColor(const Light& light, const int& depth) const {
    return Scene::getInstance()->getAmbientLightColor();
}