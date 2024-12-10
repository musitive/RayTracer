#include "Diffuse.h"
#include "Scene.h"

Diffuse::Diffuse(RGBColor diffuse, RGBColor specular, double phong) : diffuse_constant(diffuse), specular_constant(specular), phong_constant(phong) {}

RGBColor Diffuse::computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) {
    if (blocked) return computeBlockedColor();
    else return computeColorFromLight(i, light);
}

RGBColor Diffuse::computeBlockedColor() {
    RGBColor ambient_lighting = Scene::getInstance()->getGlobalIllumination();
    return clamp(diffuse_constant * ambient_lighting, MIN_COLOR, MAX_COLOR);
}

RGBColor Diffuse::computeColorFromLight(const AbstractIntersect* i, const Light& light) {   
    Direction to_light = Direction(light.position, i->point);
    double diffuse_intensity = dot(to_light, i->computeNormal());

    RGBColor diffuse = computeDiffuseColor(light.color, diffuse_intensity);
    RGBColor specular = computeSpecularColor(i, light.color, diffuse_intensity, to_light);
    RGBColor c = diffuse + specular;

    return clamp(c, MIN_COLOR, MAX_COLOR);
}

RGBColor Diffuse::computeDiffuseColor(const RGBColor& light_color, const double& diffuse_intensity) const {
    RGBColor diffuse_lighting = light_color * max(0.0, diffuse_intensity);
    RGBColor ambient_lighting = Scene::getInstance()->getGlobalIllumination();
    return diffuse_constant * (ambient_lighting + diffuse_lighting);
}

RGBColor Diffuse::computeSpecularColor(const AbstractIntersect* i, const RGBColor& light_color, const double& diffuse_intensity, const Direction& to_light) const {
    Direction view = Direction(i->ray.origin, i->point);
    Direction light_reflection = Direction(i->normal * (diffuse_intensity * 2), to_light);
    double specular_intensity = max(0.0, dot(view, light_reflection));
    double specular_component = pow(specular_intensity, phong_constant);
    return light_color * specular_constant * specular_component;
}