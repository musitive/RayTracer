#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vec.h"

using namespace std;

struct Light {
    Colord color;
    Position position;
};

class Material {
    public:
        bool isReflective = false;
        virtual Colord computeColor(const Position& from, const Position& p, const Direction& n, const Light& light, const bool& blocked, const Colord& ambient) = 0;
};

class Diffuse : public Material {
    public:
        Colord diffuse;
        Colord specular;
        double phong;
    public:
        Diffuse(Colord diffuse, Colord specular, double phong) : diffuse(diffuse), specular(specular), phong(phong) {}
        Colord computeColor(const Position& from, const Position& p, const Direction& n, const Light& light, const bool& blocked, const Colord& ambient) override {

            Colord d(0);
            Colord ph(0);

            if (!blocked) {
                Direction l = Direction(light.position - p);
                double dt = dot(l, n);
                Direction r = n * (dt * 2) - l;
                d = light.color * max(0.0, dt);
                Direction v = from - p;
                ph = light.color * specular * pow(max(0.0, dot(v, r)), phong);
                return bound(diffuse * (ambient + d) + ph);
            }

            return bound(diffuse * ambient + d);
        }
};

class Reflective : public Material {
    public:
        Colord reflective;
    public:
        Reflective(Colord reflective) : reflective(reflective) { isReflective = true; }
        Colord computeColor(const Position& from, const Position& p, const Direction& n, const Light& light, const bool& blocked, const Colord& ambient) override {
            return bound(reflective);
        }
};

#endif