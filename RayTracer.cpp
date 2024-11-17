#include "RayTracer.h"

Colord RayTracer::calculateReflection(const Ray& ray, Intersection closest_intersection, Environment* env, const int& depth) {
    Direction n = closest_intersection.closest->computeNormal(closest_intersection.p);
    double dt = dot(ray.direction, n);
    Direction r = n * dt * 2 - ray.direction;
    Light light = { env->light.color, env->light.position };
    Ray newRay(closest_intersection.p, -r);

    Colord cd = closest_intersection.closest->computeColor(ray.origin, closest_intersection.p, light, false, env->ambient_light);
    Colord ct = trace(newRay, env, closest_intersection.closest, depth+1);

    // If image looks bad it's this line  -- LEAVE THIS COMMENT IN IN CASE OF FUTURE BUGS
    return ct * cd;
}

Intersection RayTracer::findClosestIntersection(const Ray& ray, Environment* env, Object* current) {
    Object* closest = NULL;

    Position p = Position(numeric_limits<double>::infinity());
    Position np = Position(numeric_limits<double>::infinity());

    double previous_length = numeric_limits<double>::infinity();
    double next_length = numeric_limits<double>::infinity();

    for(Object* o: env->env) {
        if (o != current) {
            np = o->calculateIntersection(ray);
            next_length = length(np - ray.origin);
            if(next_length < previous_length) {
                closest = o;
                p = np;
                previous_length = next_length;
            }
        }
    }

    return { closest, p };
}

Colord RayTracer::trace(const Ray& ray, Environment* env, Object* current, const int& depth) {
    if (depth >= MAX_DEPTH)
        return Colord(1);
    
    Intersection closest_intersection = findClosestIntersection(ray, env, current);

    if (!closest_intersection.closest)
        return env->background;
    else if (closest_intersection.closest->getMaterial()->isReflective)
        return calculateReflection(ray, closest_intersection, env, depth);
    else {
        bool blocked = false;
        Light light = env->light;
        Direction l = light.position - closest_intersection.p;
        Ray to_light(closest_intersection.p, l);
        double distance = length(light.position - closest_intersection.p);
        for (Object* o: env->env) {
            if (o != closest_intersection.closest) {
                if (length(light.position - o->calculateIntersection(to_light, false)) < distance) {
                    blocked = true;
                    break;
                }
            }
        }
        return closest_intersection.closest->computeColor(ray.origin, closest_intersection.p, light, blocked, env->ambient_light);
    }
}