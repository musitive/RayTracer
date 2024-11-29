#ifndef SCENE_H
#define SCENE_H

#include "Environment.h"
#include "RayTracer.h"
#include "Camera.h"

class Scene {
    public:
        static Scene* initializeInstance(Environment* env, Camera* cam) {
            if (!env || !cam) throw invalid_argument("Environment and Camera must be provided");

            instance = new Scene(env, cam);
            return instance;
        }

        static void destroyInstance() {
            if (instance) {
                delete instance;
                instance = nullptr;
            }
        }

        static Scene* getInstance() {
            return instance;
        }

        static Environment* getEnvironment() {
            return instance->env;
        }

        static Colord getAmbientLightColor() {
            return instance->env->background;
        }

        Frame* render();
        int getCameraWidth() const;
        int getCameraHeight() const;

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

    private:
        Environment* env;
        Camera* cam;

        // Static pointer to the Singleton instance
        static Scene* instance;

        Scene(Environment* env, Camera* cam);
        ~Scene();
};
#endif