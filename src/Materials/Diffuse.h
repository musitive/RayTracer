#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "IMaterial.h"

class Diffuse : public IMaterial {
    public:
        Diffuse(Colord diffuse, Colord specular, double phong);
        Colord computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) override;

    private:
        const Colord diffuse_constant, specular_constant;
        const double phong_constant;
        Colord computeBlockedColor();
        Colord computeColorFromLight(const AbstractIntersect* i, const Light& light);
        inline Colord computeDiffuseColor(const Colord& light_color, const double& diffuse_intensity) const;
        inline Colord computeSpecularColor(const AbstractIntersect* i, const Colord& light_color, const double& diffuse_intensity, const Direction& to_light) const;
};

#endif