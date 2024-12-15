#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "IMaterial.h"

class Diffuse : public IMaterial {
    public:
        Diffuse(RGBColor diffuse, RGBColor specular, double phong);
        RGBColor computeColor(const AbstractIntersection* i, const Light& light, const bool& blocked) override;

    private:
        const RGBColor diffuse_constant, specular_constant;
        const double phong_constant;
        RGBColor computeBlockedColor();
        RGBColor computeColorFromLight(const AbstractIntersection* i, const Light& light);
        inline RGBColor computeDiffuseColor(const RGBColor& light_color, const double& diffuse_intensity) const;
        inline RGBColor computeSpecularColor(const AbstractIntersection* i, const RGBColor& light_color, const double& diffuse_intensity, const Direction& to_light) const;
};

#endif