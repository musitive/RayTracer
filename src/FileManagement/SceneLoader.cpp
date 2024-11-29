#include "SceneLoader.h"
#include "Scene.h"
#include "AntiAliasCam.h"

std::ifstream SceneLoader::input_file = std::ifstream();
Scene* SceneLoader::scene = nullptr;

void SceneLoader::loadScene(const string& fileName) {
    string line_header = "";

    input_file.open(fileName, ios::in);
    Camera* cam = parseCamera();
    Light light = Light();
    Colord ambient_light = Colord();
    Colord background = Colord();

    input_file >> line_header >> light.position;
    input_file >> line_header >> light.color;
    input_file >> line_header >> ambient_light;
    input_file >> line_header >> background;

    scene = Scene::initializeInstance(light, ambient_light, background, cam);

    parseObjects();

    input_file.close();
}

Camera* SceneLoader::parseCamera() {
    string line_header = "";
    double width, height, fov;
    Point3D at, from, up;

    input_file >> line_header >> width >> line_header >> height;
    input_file >> line_header >> at;
    input_file >> line_header >> from;
    input_file >> line_header >> up;
    input_file >> line_header >> fov;

    return new Camera(width, height, at, from, up, fov);
}

void SceneLoader::parseObjects() {
    string line_header;
    AbstractObject* o;
    IMaterial* m;

    input_file >> line_header;
    while(!input_file.eof()) {
        o = parseObject(line_header);

        input_file >> line_header >> line_header;
        m = parseMaterial(line_header);
        
        o->setMaterial(m);
        scene->addActor(o);
        input_file >> line_header;
    }
}

AbstractObject* SceneLoader::parseObject(string line_header) {
    AbstractObject* o;

    if (line_header == "Sphere")
        o = parseSphere();
    else if (line_header == "Triangle")
        o = parseTriangle();

    return o;
}

Sphere* SceneLoader::parseSphere() {
    string line_header;
    Point3D c = Point3D();
    double rad = 0;
    input_file >> line_header >> c;
    input_file >> line_header >> rad;
    return new Sphere(c, rad);
}

Triangle* SceneLoader::parseTriangle() {
    Point3D v1, v2, v3;
    input_file >> v1;
    input_file >> v2;
    input_file >> v3;
    return new Triangle(v1, v2, v3);
}

IMaterial* SceneLoader::parseMaterial(string line_header) {
    IMaterial* m;

    if (line_header == "Diffuse") 
        m = parseDiffuseMaterial();
    else if (line_header == "Reflective")
        m = parseReflectiveMaterial();

    return m;
}

Diffuse* SceneLoader::parseDiffuseMaterial() {
    string line_header;
    Colord diffuse = Colord();
    Colord specular = Colord();
    double phong = 0;
    input_file >> diffuse;
    input_file >> line_header >> specular;
    input_file >> line_header >> phong;
    return new Diffuse(diffuse, specular, phong);
}

Reflective* SceneLoader::parseReflectiveMaterial() {
    string line_header;
    Colord reflective = Colord();
    input_file >> reflective;
    return new Reflective(reflective);
}

void SceneLoader::unloadScene() {
    Scene::destroyInstance();
}