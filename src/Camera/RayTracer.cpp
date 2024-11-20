#include "RayTracer.h"

RayTracer::RayTracer(Environment* env) {
    this->env = env;
}

Colord RayTracer::trace(const Ray& ray, Object* reflected_object, const int& depth) {
    if (depth >= MAX_DEPTH) return Colord(1);
    
    Intersection closest_intersection = findClosestIntersection(ray, reflected_object);
    Colord color = Colord(1);

    if (!closest_intersection.getObject()) return env->background;

    if (closest_intersection.getObject()->getMaterial()->isReflective)
        color = calculateReflection(closest_intersection, depth);
    else
        color = calculateDiffuse(closest_intersection);

    return color;
}

Intersection RayTracer::findClosestIntersection(const Ray& ray, Object* reflected_object) {
    Intersection closest_intersection = Intersection();
    Intersection new_intersection = Intersection();

    for(Object* o: env->env) {
        if (o == reflected_object) continue;

        new_intersection = Intersection(o, ray);

        if (new_intersection.isCloserThan(closest_intersection))
            closest_intersection = new_intersection;
    }

    return closest_intersection;
}

Colord RayTracer::calculateReflection(const Intersection& i, const int& depth) {
    Direction normal = i.computeNormal();
    Direction ray_direction = i.getRay().direction;
    double dt = dot(ray_direction, normal);
    Direction reflection_direction = normal * (dt * 2) - ray_direction;
    Ray reflection(i.getPosition(), -reflection_direction);

    Colord cd = i.computeColor(env->light, false, env->ambient_light);
    Colord ct = trace(reflection, i.getObject(), depth+1);

    return ct * cd;
}

Colord RayTracer::calculateDiffuse(const Intersection& i) {
    bool blocked = isObjectBlocked(i, env->light.position);
    
    return i.getObject()->computeColor(i.getRay().origin, i.getPosition(), env->light, blocked, env->ambient_light);
}

bool RayTracer::isObjectBlocked(const Intersection& i, const Point3D& light_position) {
    Direction direction_to_light = light_position - i.getPosition();
    double distance = length(light_position - i.getPosition());
    Ray to_light(i.getPosition(), direction_to_light);

    for (Object* o: env->env)
        if (o != i.getObject() && o->isBlocking(to_light, light_position, distance))
            return true;

    return false;
}