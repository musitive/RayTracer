#include "RayTracer.h"

Colori RayTracer::calculateReflection(Ray ray, Position p, Object* closest, Environment* env, const int& depth) {
    Direction n = closest->computeNormal(p);
    double dt = dot(ray.direction, n);
    Direction r = n * dt * 2 - ray.direction;
    Light light = { env->light.color, env->light.position };
    Ray newRay(p, -r);
    Colori ci = closest->computeColor(ray.origin, p, light, false, env->ambient_light);
    Colord cd = Colord(ci.x/255.,ci.y/255.,ci.z/255.);
    Colori ct = trace(newRay, env, closest, depth+1);

    return Colori(ct.x*cd.x,ct.y*cd.y,ct.z*cd.z);
}

Colori RayTracer::trace(Ray ray, Environment* env, Object* current, const int& depth) {
    if (depth >= MAX_DEPTH)
        return Colori(255);

    Position p = Position(numeric_limits<double>::infinity());
    Object* closest = NULL;
    double previous_length = numeric_limits<double>::infinity();
    double next_length = numeric_limits<double>::infinity();

    for(Object* o: env->env) {
        if (o != current) {
            Position np = o->calculateIntersection(ray);
            next_length = length(np - ray.origin);
            if(next_length < previous_length) {
                closest = o;
                p = np;
                previous_length = next_length;
            }
        }
    }
    
    if (!closest)
        return Colori(env->background.x*255,env->background.y*255,env->background.z*255);
    else if (closest->getMaterial()->isReflective)
        return calculateReflection(ray, p, closest, env, depth);
    else {
        bool blocked = false;
        Light light = env->light;
        Direction l = light.position - p;
        Ray to_light(p, l);
        double distance = length(light.position - p);
        for (Object* o: env->env) {
            if (o != closest) {
                if (length(light.position - o->calculateIntersection(to_light, false)) < distance) {
                    blocked = true;
                    break;
                }
            }
        }
        return closest->computeColor(ray.origin, p, light, blocked, env->ambient_light);
    }
}