int main(int argc, char** argv) {
    char* input_filename = argv[1];
    char* output_filename = argv[2];

    srand(time(0));

    SceneLoader::loadScene(input_filename);

    Scene* scene = Scene::getInstance();
    Frame* frame = scene->render();

    PPM::writeToFile(output_filename, frame, 255);

    free(frame);
    SceneLoader::unloadScene();

    return 0;
}

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