#include <random>
#include "Scene.h"
#include "Frame.h"
#include "SceneBuilder.h"
#include "PPM.h"

int main(int argc, char **argv) {
    char *input_filename = argv[1];
    char *output_filename = argv[2];

    srand(time(0)); // Create seed for the random number generator

    // I'm not including the SceneBuilder, Frame, or PPM classes in this code sample
    // because they mostly deal with file I/O and are not relevant to the ray tracer
    // and they should be self-evident from the context provided here.
    SceneBuilder::loadScene(input_filename);

    Scene *scene = Scene::getInstance();    // Get pointer to the Singleton instance of the Scene
    Frame *frame = scene->render();

    PPM::writeToFile(output_filename, frame);

    free(frame);
    SceneBuilder::unloadScene();

    return 0;
}