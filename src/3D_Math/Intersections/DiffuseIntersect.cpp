#include "DiffuseIntersect.h"
#include "Scene.h"

Absorption::Absorption(Actor* o, const Ray& r, const Point3D& p) : AbstractIntersection(o, r, p) {}

RGBColor Absorption::computeColor(const Light& light, const int& depth) const {
    bool blocked = isBlocked(light.position);
    
    return obj->getMaterial()->computeColor(this, light, blocked);
}

bool Absorption::isBlocked(const Point3D& light_position) const {
    Direction direction_to_light = light_position - point;
    double distance = length(light_position - point);
    Ray to_light(point, direction_to_light);
    vector<Actor*> actors = Scene::getInstance()->getActors();

    for (Actor* o: actors)
        if (o != obj && o->isBlocking(to_light, light_position, distance))
            return true;

    return false;
}