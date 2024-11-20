#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "IMaterial.h"

class Diffuse : public IMaterial {
    public:
        Diffuse(Colord diffuse, Colord specular, double phong);
        Colord computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked, const Colord& ambient) override;

    public:
        Colord diffuse, specular;
        double phong;

        Colord computeColorFromLight(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const Colord& ambient);
        Colord computeBlockedColor(const Colord& ambient);
};

#endif