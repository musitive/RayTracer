#include "FileManager.h"
#include "Object.h"
#include "Vec.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Material.h"
#include "Vec.h"

using namespace std;

FileManager::FileManager() {}

Environment* FileManager::readFile(const string& fileName) {
    string line_header;
    env = new Environment();

    input_file.open(fileName, ios::in);
    input_file >> line_header >> env->cam.width >> line_header >> env->cam.height;
    input_file >> line_header >> env->cam.at;
    input_file >> line_header >> env->cam.from;
    input_file >> line_header >> env->cam.up;
    input_file >> line_header >> env->cam.fov;
    input_file >> line_header >> env->light_position;
    input_file >> line_header >> env->light_color;
    input_file >> line_header >> env->ambient_light;
    input_file >> line_header >> env->background;

    parseObjects();

    input_file.close();
    return env;
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
    output_file << "P3" << endl;
    output_file << "# " << fileName << endl;
    output_file << w << ' ' << h << endl;
    output_file << max_color << endl;
}

void FileManager::addColor(const Colori& color) {
    output_file << color << endl;
}

void FileManager::closeOutput() {
    output_file.close();
}
