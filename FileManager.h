#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include "Vec.h"
#include "Environment.h"
#include "Triangle.h"
#include "Sphere.h"

using namespace std;

class FileManager {
    public:
        FileManager();

        Environment* readFile(const string& filename);
        Camera* parseCamera();
        void parseObjects();
        Object* parseObject(string line_header);
        Sphere* parseSphere();
        Triangle* parseTriangle();
        Material* parseMaterial(string line_header);
        Diffuse* parseDiffuseMaterial();
        Reflective* parseReflectiveMaterial();

        void prepOutputFile(const string& filename, const int& w, const int& h, const int& max_color);
        void addColor(const Colori& color);
        void closeOutput();

    private:
        ifstream input_file;
        ofstream output_file;
        Environment* env;
};

#endif