#include "Diffuse.h"

Diffuse::Diffuse(Colord diffuse, Colord specular, double phong) : diffuse(diffuse), specular(specular), phong(phong) {}

Colord Diffuse::computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked, const Colord& ambient) {
    Colord color(0);

    if (blocked)
        color = computeBlockedColor(ambient);
    else
        color = computeColorFromLight(from, p, n, light, ambient);

    return color;
}

Colord Diffuse::computeBlockedColor(const Colord& ambient) {
    return bound(diffuse * ambient);
}

Colord Diffuse::computeColorFromLight(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const Colord& ambient) {
    Colord d(0);
    Colord ph(0);
    
    Direction l = Direction(light.position - p);
    double dt = dot(l, n);
    Direction r = n * (dt * 2) - l;
    d = light.color * max(0.0, dt);
    Direction v = from - p;
    ph = light.color * specular * pow(max(0.0, dot(v, r)), phong);
    return bound(diffuse * (ambient + d) + ph);
}