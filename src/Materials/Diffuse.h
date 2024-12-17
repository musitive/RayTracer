#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "IMaterial.h"
#include "Direction.h"

class Diffuse : public IMaterial {
    public:
        Diffuse(RGBColor diffuse, RGBColor specular, double phong) :
            diffuse_constant(diffuse), specular_constant(specular), phong_constant(phong) {}
        RGBColor computeColor( const AbstractIntersect *i, const Light &light, const bool &blocked) override;
        bool isReflective() override;

    private:
        const RGBColor diffuse_constant, specular_constant;
        const double phong_constant;

        RGBColor computeBlockedColor();
        RGBColor computeColorFromLight(const AbstractIntersect *i, const Light &light);
        RGBColor computeDiffuseColor(const RGBColor &light_color, const double &diffuse_intensity) const;
        RGBColor computeSpecularColor(const AbstractIntersect *i, const RGBColor &light_color,
            const double &diffuse_intensity, const Direction &to_light) const;
};

#endif