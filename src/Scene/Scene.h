#ifndef SCENE_H
#define SCENE_H

#include "RayTracer.h"
#include "Camera.h"
#include "KDTree.h"

/**
 * The Scene class is a Singleton that holds all of the actors in the scene.
 * While Singletons can be controversial, I chose to use one here because there
 * should only ever be one scene in the program. Plus, it seems like the cleanest
 * way to handle what are essentially global variables. If this were a game engine,
 * mutexes could be implemented to ensure thread safety.
*/
class Scene {
    public:
        // For my purposes, only one scene will ever be created. If this were a
        // game engine and I swap out scenes, it could be changed here.
        static Scene* createInstance(const Light& light, const RGBColor& global,
                                     const RGBColor& background, Camera* cam) {

            if (!instance) instance = new Scene(light, global, background, cam);
            return instance;
        }

        // Including this to demonstrate how to destroy the Singleton instance.
        static void destroyInstance() {
            if (instance) {
                delete instance;
                instance = nullptr;
            }
        }

        // This is how other classes will get a pointer to the Singleton instance.
        static Scene* getInstance() {
            if (!instance) throw std::invalid_argument("Scene instance does not exist");
            return instance;
        }

        Frame* render();
        void addActor(AbstractObject* actor);

        int getCameraWidth() const;
        int getCameraHeight() const;
        vector<AbstractObject*> getActors() const;
        RGBColor getGlobalIllumination() const;
        RGBColor getBackgroundColor() const;
        Light getLight() const;

        // The copy constructor and assignment operator must be deleted to
        // prevent copying the Singleton instance
        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

    private:
        Light light;
        RGBColor global;
        RGBColor background;
        std::vector<AbstractObject*> actors;
        Camera* cam;

        // Static pointer to the Singleton instance
        static Scene* instance;

        Scene(const Light& light, const RGBColor& global, const RGBColor& background, Camera* cam);
        ~Scene();
};
#endif