#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <iostream>
#include <fstream>

#include "Vec.h"
#include "Environment.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Diffuse.h"
#include "Reflective.h"
#include "Camera.h"

class SceneLoader {
    public:
        static void loadScene(const std::string& fileName);

    private:
        static std::ifstream input_file;
        static Environment* env;

        static Camera* parseCamera();
        static void parseObjects();
        static AbstractObject* parseObject(string line_header);
        static Sphere* parseSphere();
        static Triangle* parseTriangle();
        static IMaterial* parseMaterial(string line_header);
        static Diffuse* parseDiffuseMaterial();
        static Reflective* parseReflectiveMaterial();
};

#endif