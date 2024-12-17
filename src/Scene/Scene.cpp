#include "Scene.h"
#include "Camera.h"

Scene* Scene::instance = nullptr;

Scene::Scene(const Light& light, const RGBColor& background, const RGBColor& global, Camera* cam)
    : light(light), global(global), background(background), cam(cam)
{
    if (instance) throw std::invalid_argument("Scene instance already exists");
}

Frame* Scene::render() {
    RayTracer::kd_tree = new KDTree(actors);
    return cam->render();
}

void Scene::addActor(AbstractObject* actor) {
    actors.push_back(actor);
}

int Scene::getCameraWidth() const {
    return cam->getWidth();
}

int Scene::getCameraHeight() const {
    return cam->getHeight();
}

std::vector<AbstractObject*> Scene::getActors() const {
    return actors;
}

RGBColor Scene::getGlobalIllumination() const {
    return global;
}

RGBColor Scene::getBackgroundColor() const {
    return background;
}

Light Scene::getLight() const {
    return light;
}

Scene::~Scene() {
    delete cam;
    for (AbstractObject* o : actors) {
        delete o;
    }
}