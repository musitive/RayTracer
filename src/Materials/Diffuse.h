#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "IMaterial.h"

class Diffuse : public IMaterial {
    public:
        Diffuse(Colord diffuse, Colord specular, double phong);
        Colord computeColor(const Point3D& from, const Point3D& p, const Direction& n, const Light& light, const bool& blocked) override;

    private:
        const Colord diffuse_constant, specular_constant;
        const double phong_constant;
        Colord computeBlockedColor();
        Colord computeColorFromLight(const Point3D& from, const Point3D& p, const Direction& n, const Light& light);
        Colord computeDiffuseColor(const Colord& light_color, const double& diffuse_intensity);
        Colord computeSpecularColor(const Point3D& look_from, const Point3D& point, const Colord& light_color, const Direction& normal, const double& diffuse_intensity, const Direction& to_light);
};

#endif