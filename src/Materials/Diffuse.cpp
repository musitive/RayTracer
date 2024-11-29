#include "Diffuse.h"
#include "Scene.h"

Diffuse::Diffuse(Colord diffuse, Colord specular, double phong) : diffuse_constant(diffuse), specular_constant(specular), phong_constant(phong) {}

Colord Diffuse::computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) {
    if (blocked) return computeBlockedColor();
    else return computeColorFromLight(i->ray.origin, i->point, i->computeNormal(), light);
}

Colord Diffuse::computeBlockedColor() {
    return clamp(diffuse_constant * Scene::getAmbientLightColor(), MIN_COLOR, MAX_COLOR);
}

Colord Diffuse::computeColorFromLight(const Point3D& from, const Point3D& point, const Direction& normal, const Light& light) {   
    Direction to_light = Direction(light.position, point);
    double diffuse_intensity = dot(to_light, normal);

    Colord diffuse = computeDiffuseColor(light.color, diffuse_intensity);
    Colord specular = computeSpecularColor(from, point, light.color, normal, diffuse_intensity, to_light);
    Colord c = diffuse + specular;

    return clamp(c, MIN_COLOR, MAX_COLOR);
}

Colord Diffuse::computeDiffuseColor(const Colord& light_color, const double& diffuse_intensity) {
    Colord diffuse_lighting = light_color * max(0.0, diffuse_intensity);
    return diffuse_constant * (Scene::getAmbientLightColor() + diffuse_lighting);
}

Colord Diffuse::computeSpecularColor(const Point3D& from, const Point3D& point, const Colord& light_color, const Direction& normal, const double& diffuse_intensity, const Direction& to_light) {
    Direction view = Direction(from, point);
    Direction light_reflection = Direction(normal * (diffuse_intensity * 2), to_light);
    double specular_intensity = max(0.0, dot(view, light_reflection));
    double specular_component = pow(specular_intensity, phong_constant);
    return light_color * specular_constant * specular_component;
}