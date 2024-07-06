#pragma once
#include <iostream>
#include <fstream>
#include "Vec.h"
#include "Scene.h"
#include "Triangle.h"
#include "Sphere.h"
#include "LightSource.h"

using namespace std;

class Parser {
    private:
        ifstream input_file;
        string current_label;
        Scene* scene;

        void parseCamera();
        void parseSceneLighting();
        void parseObjectsInScene();
        Position parseLabeledPosition();
        Colord parseLabeledColord();
        double parseLabeledDouble();
        Object* createObject();
        Object* createTriangle();
        Object* createSphere();
        Material* createMaterial();
        Material* createDiffuseMaterial();
        Material* createReflectiveMaterial();

    public:
        Parser();
        Scene* createEnvironmentFromFile(const string& filename);
};
