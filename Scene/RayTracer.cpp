#include "RayTracer.h"

Colori RayTracer::trace(Ray ray, Environment* env, Object* current, const int& depth) {
    if (depth >= MAX_DEPTH)
        return Colori(255);

    Colori color = Colori(env->background.x*255,env->background.y*255,env->background.z*255);
    Object* closest = findClosestIntersection(ray, &env->env, current);
    
    if (closest != nullptr)
        color = calculateColorAtIntersection(ray, env, closest, depth);
    
    return color;
}

Object* RayTracer::findClosestIntersection(Ray ray, vector<Object*>* objects, Object* origin_object) {
    Object* closest = nullptr;
    Position closestIntersectPoint = Position(numeric_limits<double>::infinity());

    for(Object* o: *objects) {
        if (o == origin_object) continue;

        Position intersectPoint = o->calculateIntersection(ray);
        if(length(intersectPoint - ray.origin) < length(closestIntersectPoint - ray.origin)) {
            closest = o;
            closestIntersectPoint = intersectPoint;
        }
    }
    
    return closest;
}

Colori RayTracer::calculateColorAtIntersection(Ray ray, Environment* env, Object* object, const int& depth) {
    bool blocked = false;
    LightSource light = env->getLightSource();
    Direction l = light.position - p;
    Ray toLight(p, l);
    double distance = length(light.position - p);
    for (Object* o: env->env) {
        if (o == closest) continue;
        if (length(light.position - o->calculateIntersection(toLight, false)) < distance) {
            blocked = true;
            break;
        }
    }
    if (closest->getMaterial()->isReflective) {
        Direction n = closest->computeNormal(p);
        double dt = dot(ray.direction, n);
        Direction r = n * dt * 2 - ray.direction;
        Ray newRay(p, -r);
        Colori ci = closest->computeColor(ray.origin, p, light, false, env->ambient_light);
        Colord cd = Colord(ci.x/255.,ci.y/255.,ci.z/255.);
        Colori ct = Colori();
        for(int y = 0; y < 4; y++) {
            ct = ct + trace(newRay, env, closest, depth+1);
        }
        ct = ct / 4;
        return Colori(ct.x*cd.x,ct.y*cd.y,ct.z*cd.z);
    }
    else
        return closest->computeColor(ray.origin, p, light, blocked, env->ambient_light);
}