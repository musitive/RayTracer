#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include <iostream>
#include <fstream>

#include "Vec.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Diffuse.h"
#include "Reflective.h"
#include "Camera.h"
#include "Scene.h"

class SceneBuilder {
    public:
        static void loadScene(const std::string& fileName);
        static void unloadScene();

    private:
        static std::ifstream input_file;
        static Scene* scene;

        static Camera* parseCamera();
        static void parseObjects();
        static Actor* parseObject(string line_header);
        static Sphere* parseSphere();
        static Triangle* parseTriangle();
        static IMaterial* parseMaterial(string line_header);
        static Diffuse* parseDiffuseMaterial();
        static Reflective* parseReflectiveMaterial();
};

#endif