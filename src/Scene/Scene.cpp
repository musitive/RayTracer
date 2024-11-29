#include "Scene.h"
#include "Camera.h"

Scene* Scene::instance = nullptr;

Scene::Scene(const Light& light, const Colord& ambient_light, const Colord& background, Camera* cam)
    : light(light), ambient_light(ambient_light), background(background), cam(cam)
{
    if (instance) throw invalid_argument("Scene instance already exists");
}

Frame* Scene::render() {
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

vector<AbstractObject*> Scene::getActors() const {
    return actors;
}

Colord Scene::getAmbientLightColor() const {
    return ambient_light;
}

Colord Scene::getBackgroundColor() const {
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