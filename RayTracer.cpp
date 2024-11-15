#include "RayTracer.h"

Ray RayTracer::computeRay(double i, double j, double angle, double aspectratio, Environment* env) {
    double xx = (2 * (i * 1/env->cam.width) - 1) * angle * aspectratio;
    double yy = (1 - 2 * (j * 1/env->cam.height)) * angle;
    Position look_from = env->cam.from;
    Position look_at = Position(xx,yy,0) + env->cam.at;

    Ray ray = Ray(look_from, look_at);
    return ray;
}

Colori RayTracer::calculateReflection(Ray ray, Position p, Object* closest, Environment* env, const int& depth) {
    Direction n = closest->computeNormal(p);
    double dt = dot(ray.direction, n);
    Direction r = n * dt * 2 - ray.direction;
    Light light = { env->light_color, env->light_position };
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

    for(Object* o: env->env) {
        if (o != current) {
            Position np = o->calculateIntersection(ray);
            if(length(np - ray.origin) < length(p - ray.origin)) {
                closest = o;
                p = np;
            }
        }
    }
    
    if (!closest)
        return Colori(env->background.x*255,env->background.y*255,env->background.z*255);
    else {
        bool blocked = false;
        Light light = { env->light_color, env->light_position };
        Direction l = light.position - p;
        Ray toLight(p, l);
        double distance = length(light.position - p);
        for (Object* o: env->env) {
            if (o != closest) {
                if (length(light.position - o->calculateIntersection(toLight, false)) < distance) {
                    blocked = true;
                    break;
                }
            }
        }
        if (closest->getMaterial()->isReflective) {
            return calculateReflection(ray, p, closest, env, depth);
        }
        else {
            return closest->computeColor(ray.origin, p, light, blocked, env->ambient_light);
        }
    }
}