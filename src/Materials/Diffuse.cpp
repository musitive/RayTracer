#include "Diffuse.h"
#include "Scene.h"

RGBColor Diffuse::computeColor(const AbstractIntersect *i, const Light &light, const bool &blocked) {
    if (blocked) return computeBlockedColor();
    return computeColorFromLight(i, light);
}

// Computes the color of the object when it is blocked from the light.
RGBColor Diffuse::computeBlockedColor() {
    RGBColor ambient_lighting = Scene::getInstance()->getGlobalIllumination();
    return clamp(diffuse_constant * ambient_lighting);
}

// Computes the color of the object when it is illuminated by a light source.
RGBColor Diffuse::computeColorFromLight(const AbstractIntersect *i, const Light &light) {   
    Direction to_light = Direction(light.position, i->hit_point);
    double diffuse_intensity = dot(to_light, i->computeActorNormal());

    RGBColor diffuse = computeDiffuseColor(light.color, diffuse_intensity);
    RGBColor specular = computeSpecularColor(i, light.color, diffuse_intensity, to_light);

    return clamp(diffuse + specular);
}

// Computes the diffuse portion of the color.
RGBColor Diffuse::computeDiffuseColor(const RGBColor &light_color, const double &diffuse_intensity) const {
    RGBColor diffuse_lighting = light_color * rt_lib::max(0.0, diffuse_intensity);
    RGBColor ambient_lighting = Scene::getInstance()->getGlobalIllumination();

    return diffuse_constant * (ambient_lighting + diffuse_lighting);
}

// Computes the specular portion of the color.
RGBColor Diffuse::computeSpecularColor(const AbstractIntersect *i, const RGBColor &light_color,
    const double &diffuse_intensity, const Direction &to_light) const
{
    Direction view = Direction(i->ray.origin, i->hit_point);
    Direction light_reflection = Direction(i->normal * (diffuse_intensity * 2), to_light);

    double specular_intensity = std::max(0.0, dot(view, light_reflection));
    double specular_component = pow(specular_intensity, phong_constant);

    return light_color * specular_constant * specular_component;
}

bool Diffuse::isReflective() {
    return false;
}