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
    Environment* env = new Environment();

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

    input_file >> line_header;
    while(!input_file.eof()) {
        Object* o;
        if (line_header == "Sphere") {
            Position c = Position();
            double rad = 0;
            input_file >> line_header >> c;
            input_file >> line_header >> rad;
            o = new Sphere(c, rad);
        }
        else if (line_header == "Triangle") {
            Position v1, v2, v3;
            input_file >> v1;
            input_file >> v2;
            input_file >> v3;
            o = new Triangle(v1, v2, v3);;
        }
        input_file >> line_header >> line_header;
        Material* material;
        if (line_header == "Diffuse") {
            Colord diffuse = Colord();
            Colord specular = Colord();
            double phong = 0;
            input_file >> diffuse;
            input_file >> line_header >> specular;
            input_file >> line_header >> phong;
            material = new Diffuse(diffuse, specular, phong);
        }
        else if (line_header == "Reflective") {
            Colord reflective = Colord();
            input_file >> reflective.x >> reflective.y >> reflective.z;
            material = new Reflective(reflective);
        }
        o->setMaterial(material);
        env->env.push_back(o);
        input_file >> line_header;
    }
    input_file.close();
    return env;
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
