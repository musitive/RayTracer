#include "Scene.h"
#include "RayTracer.h"

Scene::Scene() {
    light_source = { Position(), Colord() };
    ambient_light = Colord();
    background_color = Colord();
    objects = vector<Object*>();
}

Image* Scene::render() {
    const int WIDTH = camera->getWidth();
    const int HEIGHT = camera->getHeight();
    const double aspectratio = WIDTH / double(HEIGHT);
    const double angle = tan(M_PI * 0.5 * fov / 180.);

    RayTracer* ray_tracer = new RayTracer();

    srand(time(0));
    for(int row = 0; row < HEIGHT; row++) {
        for(int col = 0; col < WIDTH; col++) {
            vector<Colori> colors = ray_tracer->subdivide(col, row, 4, angle, aspectratio, scene);
            image->addColor(average(colors));
        }
    }

    return new Image();
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