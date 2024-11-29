#include "Diffuse.h"
#include "Scene.h"

Diffuse::Diffuse(Colord diffuse, Colord specular, double phong) : diffuse(diffuse), specular(specular), phong(phong) {}

Colord Diffuse::computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked) {
    Colord color(0);

    if (blocked) color = computeBlockedColor();
    else color = computeColorFromLight(from, p, n, light);

    return color;
}

Colord Diffuse::computeBlockedColor() {
    const Colord ambient = Scene::getInstance()->getEnvironment()->background;
    return bound(diffuse * ambient);
}

Colord Diffuse::computeColorFromLight(const Point3D& from, const Point3D& p, const Direction& n, const Light& light) {
    Colord d(0);
    Colord ph(0);
    const Colord ambient = Scene::getInstance()->getEnvironment()->background;
    
    Direction l = Direction(light.position - p);
    double dt = dot(l, n);
    Direction r = n * (dt * 2) - l;
    d = light.color * max(0.0, dt);
    Direction v = from - p;
    ph = light.color * specular * pow(max(0.0, dot(v, r)), phong);
    return bound(diffuse * (ambient + d) + ph);
}