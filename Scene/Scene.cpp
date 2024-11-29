#include "Scene.h"
#include "RayTracer.h"

Scene::Scene() {
    light_source = { Position(), Colord() };
    ambient_light = Colord();
    background_color = Colord();
    objects = vector<Object*>();
    ray_tracer = new RayTracer();
}

Image* Scene::render() {
    const int WIDTH = camera->getWidth();
    const int HEIGHT = camera->getHeight();

    srand(time(0));

    for(int row = 0; row < HEIGHT; row++) {
        for(int col = 0; col < WIDTH; col++) {
            Colori color = calculateColorAtPoint(col, row);
            image->addColor(color);
        }
    }

    return new Image();
}

Colori Scene::calculateColorAtPoint(double i, double j) {
    Ray ray = computeRay(i, j, camera->getAngle());
    return ray_tracer->trace(ray, this, nullptr, 0);
}

Ray Scene::computeRay(double i, double j, double angle) {
    const int WIDTH = camera->getWidth();
    const int HEIGHT = camera->getHeight();
    const double aspectratio = WIDTH / double(HEIGHT);
    double xx = (2 * (i * 1/WIDTH) - 1) * angle * aspectratio;
    double yy = (1 - 2 * (j * 1/HEIGHT)) * angle;
    Position look_from = camera->getFrom();
    Position look_at = Position(xx,yy,0) + camera->getAt();

    return Ray(look_from, look_at);
}

void Scene::addObject(Object* object) {
    objects.push_back(object);
}

void Scene::setCamera(Camera* camera) {
    this->camera = camera;
}

void Scene::setLightSource(LightSource light_source) {
    this->light_source = light_source;
}

void Scene::setAmbientLight(Colord ambient_light) {
    this->ambient_light = ambient_light;
}

void Scene::setBackgroundColor(Colord background_color) {
    this->background_color = background_color;
}