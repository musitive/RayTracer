#include "Diffuse.h"

Diffuse::Diffuse(Colord diffuse, Colord specular, double phong) {
    this->diffuse = diffuse;
    this->specular = specular;
    this->phong = phong;
}

Colori Diffuse::computeColor(Position from, Position p, Direction n, LightSource light, bool blocked, Colord ambient) override {
    Direction l = Direction(light.position - p);
    double dt = dot(l, n);

    Direction r = n * dt * 2 - l;

    Colord d(0);
    Colord ph(0);

    if (!blocked) {
        d = light.color * max(0.0, dt);
        Direction v = from - p;
        ph = light.color * specular * pow(max(0.0, dot(v, r)), phong);
    }

    return bound(diffuse * (ambient + d) + ph);
}