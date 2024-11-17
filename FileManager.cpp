#include "FileManager.h"
#include "Object.h"
#include "Vec.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Material.h"
#include "Vec.h"
#include <string> 

using namespace std;

FileManager::FileManager() {}

Environment* FileManager::readFile(const string& fileName) {
    string line_header;

    input_file.open(fileName, ios::in);
    Camera* cam = parseCamera();

    env = new Environment(cam);
    input_file >> line_header >> env->light.position;
    input_file >> line_header >> env->light.color;
    input_file >> line_header >> env->ambient_light;
    input_file >> line_header >> env->background;

    parseObjects();

    input_file.close();
    return env;
}

Camera* FileManager::parseCamera() {
    string line_header;
    double width, height, fov;
    Position at, from, up;

    input_file >> line_header >> width >> line_header >> height;
    input_file >> line_header >> at;
    input_file >> line_header >> from;
    input_file >> line_header >> up;
    input_file >> line_header >> fov;

    return new Camera(width, height, at, from, up, fov);
}

void FileManager::parseObjects() {
    string line_header;
    Object* o;
    Material* m;

    input_file >> line_header;
    while(!input_file.eof()) {
        o = parseObject(line_header);

        input_file >> line_header >> line_header;
        m = parseMaterial(line_header);
        
        o->setMaterial(m);
        env->env.push_back(o);
        input_file >> line_header;
    }
}

Object* FileManager::parseObject(string line_header) {
    Object* o;

    if (line_header == "Sphere")
        o = parseSphere();
    else if (line_header == "Triangle")
        o = parseTriangle();

    return o;
}

Sphere* FileManager::parseSphere() {
    string line_header;
    Position c = Position();
    double rad = 0;
    input_file >> line_header >> c;
    input_file >> line_header >> rad;
    return new Sphere(c, rad);
}

Triangle* FileManager::parseTriangle() {
    Position v1, v2, v3;
    input_file >> v1;
    input_file >> v2;
    input_file >> v3;
    return new Triangle(v1, v2, v3);
}

Material* FileManager::parseMaterial(string line_header) {
    Material* m;

    if (line_header == "Diffuse") 
        m = parseDiffuseMaterial();
    else if (line_header == "Reflective")
        m = parseReflectiveMaterial();

    return m;
}

Diffuse* FileManager::parseDiffuseMaterial() {
    string line_header;
    Colord diffuse = Colord();
    Colord specular = Colord();
    double phong = 0;
    input_file >> diffuse;
    input_file >> line_header >> specular;
    input_file >> line_header >> phong;
    return new Diffuse(diffuse, specular, phong);
}

Reflective* FileManager::parseReflectiveMaterial() {
    string line_header;
    Colord reflective = Colord();
    input_file >> reflective;
    return new Reflective(reflective);
}

void FileManager::prepOutputFile(const string& fileName, const int& w, const int& h, const int& max_color) {
    output_file.open(fileName, ios::out);
    output_file << "P3" << '\n';
    output_file << "# " << fileName << '\n';
    output_file << w << ' ' << h << '\n';
    output_file << max_color << '\n';
}

void FileManager::addColor(const Colori& color) {
    output_file << color << '\n';
}

void FileManager::closeOutput() {
    output_file.close();
}
