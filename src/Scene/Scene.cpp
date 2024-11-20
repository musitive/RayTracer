#include "Scene.h"
#include "Camera.h"

Scene::Scene(Environment* env, Camera* cam) {
    this->env = env;
    this->cam = cam;
}

Frame Scene::render() {
    return cam->render();
}

int Scene::getCameraWidth() const {
    return cam->getWidth();
}

int Scene::getCameraHeight() const {
    return cam->getHeight();
}