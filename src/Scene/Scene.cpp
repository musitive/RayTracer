#include "Scene.h"
#include "Camera.h"

Scene* Scene::instance = nullptr;

Scene::Scene(Environment* env, Camera* cam) {
    if (instance) throw invalid_argument("Scene instance already exists");

    this->env = env;
    this->cam = cam;
}

Frame* Scene::render() {
    return cam->render();
}

int Scene::getCameraWidth() const {
    return cam->getWidth();
}

int Scene::getCameraHeight() const {
    return cam->getHeight();
}

Scene::~Scene() {
    delete env;
    delete cam;
}