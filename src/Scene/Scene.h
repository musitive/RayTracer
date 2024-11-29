#ifndef SCENE_H
#define SCENE_H

#include "RayTracer.h"
#include "Camera.h"

class Scene {
    public:
        static Scene* initializeInstance(const Light& light, const Colord& ambient_light, const Colord& background, Camera* cam) {
            if (!cam) throw invalid_argument("Camera must be provided");
            if (!instance) instance = new Scene(light, ambient_light, background, cam);
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

        Frame* render();
        void addActor(AbstractObject* actor);

        int getCameraWidth() const;
        int getCameraHeight() const;
        vector<AbstractObject*> getActors() const;
        Colord getAmbientLightColor() const;
        Colord getBackgroundColor() const;
        Light getLight() const;

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

    private:
        Light light;
        Colord ambient_light;
        Colord background;
        vector<AbstractObject*> actors;
        Camera* cam;

        // Static pointer to the Singleton instance
        static Scene* instance;

        Scene(const Light& light, const Colord& ambient_light, const Colord& background, Camera* cam);
        ~Scene();
};
#endif