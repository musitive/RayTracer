#include "Scene.h"
#include "Camera.h"

Scene::Scene(Environment* env) {
    this->env = env;
    this->rt = new RayTracer();
}

void Scene::render(FileManager* fm, const string& output_filename) {
    const int IMAX = env->cam->width, JMAX = env->cam->height;

    fm->prepOutputFile(output_filename, IMAX, JMAX, 255);

    for(int j = 0; j < JMAX; ++j) {
        for(int i = 0; i < IMAX; ++i) {
            Ray r = env->cam->computeRay(i, j);
            Colori c = rt->trace(r, env, NULL, 0);
            fm->addColor(c);
        }
    }
    
    fm->closeOutput();
}