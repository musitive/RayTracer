#include "Diffuse.h"
#include "Scene.h"

Diffuse::Diffuse(Colord diffuse, Colord specular, double phong) : diffuse(diffuse), specular(specular), phong(phong) {}

Colord Diffuse::computeColor(const Point3D& look_from, const Point3D& point, const Direction& normal, const Light& light, const bool& blocked) {
    if (blocked) return computeBlockedColor();
    else return computeColorFromLight(look_from, point, normal, light);
}

Colord Diffuse::computeBlockedColor() {
    const Colord ambient = Scene::getEnvironment()->background;
    return clamp(diffuse * ambient, MIN_COLOR, MAX_COLOR);
}

Colord Diffuse::computeColorFromLight(const Point3D& look_from, const Point3D& point, const Direction& normal, const Light& light) {
    const Colord ambient = Scene::getEnvironment()->background;
    
    Direction to_light = Direction(light.position, point);
    Direction view = Direction(look_from, point);

    double diffuse_intensity = dot(to_light, normal);
    Direction light_reflection = Direction(normal * (diffuse_intensity * 2), to_light);
    Colord diffuse_lighting = light.color * max(0.0, diffuse_intensity);
    Colord specular_lighting = light.color * specular * pow(max(0.0, dot(view, light_reflection)), phong);
    Colord final_color = diffuse * (ambient + diffuse_lighting) + specular_lighting;
    
    return clamp(final_color, MIN_COLOR, MAX_COLOR);
}