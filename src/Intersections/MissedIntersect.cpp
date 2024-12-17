#include "MissedIntersect.h"
#include "Scene.h"

Miss::Miss(AbstractObject* o, const Ray& r)
    : AbstractIntersect(o, r, MISS, INF, vec3(0)) {}

RGBColor Miss::computeColor(const Light& light, const int& depth) const {
    return Scene::getInstance()->getGlobalIllumination();
}