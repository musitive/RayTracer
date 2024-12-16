#include "SceneBuilder.h"
#include "Scene.h"
#include "AntiAliasCam.h"

std::ifstream SceneBuilder::input_file = std::ifstream();
Scene* SceneBuilder::scene = nullptr;

void SceneBuilder::loadScene(const string& fileName) {
    string line_header = "";

    input_file.open(fileName, ios::in);
    Camera* cam = parseCamera();
    Light light = Light();
    RGBColor ambient_light = RGBColor();
    RGBColor background = RGBColor();

    input_file >> line_header >> light.position;
    input_file >> line_header >> light.color;
    input_file >> line_header >> ambient_light;
    input_file >> line_header >> background;

    scene = Scene::createInstance(light, ambient_light, background, cam);

    parseObjects();

    input_file.close();
}

Camera* SceneBuilder::parseCamera() {
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

void SceneBuilder::parseObjects() {
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

AbstractObject* SceneBuilder::parseObject(string line_header) {
    AbstractObject* o;

    if (line_header == "Sphere")
        o = parseSphere();
    else if (line_header == "Triangle")
        o = parseTriangle();

    return o;
}

Sphere* SceneBuilder::parseSphere() {
    string line_header;
    Point3D c = Point3D();
    double rad = 0;
    input_file >> line_header >> c;
    input_file >> line_header >> rad;
    return new Sphere(c, rad);
}

Triangle* SceneBuilder::parseTriangle() {
    Point3D v1, v2, v3;
    input_file >> v1;
    input_file >> v2;
    input_file >> v3;
    return new Triangle(v1, v2, v3);
}

IMaterial* SceneBuilder::parseMaterial(string line_header) {
    IMaterial* m;

    if (line_header == "Diffuse") 
        m = parseDiffuseMaterial();
    else if (line_header == "Reflective")
        m = parseReflectiveMaterial();

    return m;
}

Diffuse* SceneBuilder::parseDiffuseMaterial() {
    string line_header;
    RGBColor diffuse = RGBColor();
    RGBColor specular = RGBColor();
    double phong = 0;
    input_file >> diffuse;
    input_file >> line_header >> specular;
    input_file >> line_header >> phong;
    return new Diffuse(diffuse, specular, phong);
}

Reflective* SceneBuilder::parseReflectiveMaterial() {
    string line_header;
    RGBColor reflective = RGBColor();
    input_file >> reflective;
    return new Reflective(reflective);
}

void SceneBuilder::unloadScene() {
    Scene::destroyInstance();
}