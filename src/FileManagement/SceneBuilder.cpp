#include "SceneBuilder.h"
#include "Scene.h"
#include "AntiAliasCam.h"
#include "Diffuse.h"

std::ifstream SceneBuilder::input_file = std::ifstream();
Scene* SceneBuilder::scene = nullptr;

void SceneBuilder::loadScene(const std::string& fileName) {
    std::string line_header = "";
    int max_depth = 0;
    input_file.open(fileName, std::ios::in);

    input_file >> line_header >> max_depth;
    Camera* cam = parseCamera();
    Light light = Light();
    RGBColor ambient_light = RGBColor();
    RGBColor background = RGBColor();

    input_file >> line_header >> light.position;
    input_file >> line_header >> light.color;
    input_file >> line_header >> ambient_light;
    input_file >> line_header >> background;

    scene = Scene::createInstance(light, ambient_light, background, cam);
    scene->max_depth = max_depth;

    parseObjects();

    input_file.close();
}

Camera* SceneBuilder::parseCamera() {
    std::string line_header = "";
    double width, height, fov;
    vec3 at, from, up;
    int samples;

    input_file >> line_header >> samples;
    input_file >> line_header >> width >> line_header >> height;
    input_file >> line_header >> at;
    input_file >> line_header >> from;
    input_file >> line_header >> up;
    input_file >> line_header >> fov;

    if (samples > 1)
        return new AntiAliasCam(width, height, at, from, up, fov, samples);
    else
        return new Camera(width, height, at, from, up, fov);
}

void SceneBuilder::parseObjects() {
    std::string line_header;
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

AbstractObject* SceneBuilder::parseObject(std::string line_header) {
    AbstractObject* o;

    if (line_header == "Sphere")
        o = parseSphere();
    else if (line_header == "Triangle")
        o = parseTriangle();

    return o;
}

Sphere* SceneBuilder::parseSphere() {
    std::string line_header;
    vec3 c = vec3();
    double rad = 0;
    input_file >> line_header >> c;
    input_file >> line_header >> rad;
    return new Sphere(c, rad);
}

Triangle* SceneBuilder::parseTriangle() {
    vec3 v1, v2, v3;
    input_file >> v1;
    input_file >> v2;
    input_file >> v3;
    return new Triangle(v1, v2, v3);
}

IMaterial* SceneBuilder::parseMaterial(std::string line_header) {
    IMaterial* m;

    if (line_header == "Diffuse") 
        m = parseDiffuseMaterial();
    else if (line_header == "Reflective")
        m = parseReflectiveMaterial();

    return m;
}

Diffuse* SceneBuilder::parseDiffuseMaterial() {
    std::string line_header;
    RGBColor diffuse = RGBColor();
    RGBColor specular = RGBColor();
    double phong = 0;
    input_file >> diffuse;
    input_file >> line_header >> specular;
    input_file >> line_header >> phong;
    return new Diffuse(diffuse, specular, phong);
}

Reflective* SceneBuilder::parseReflectiveMaterial() {
    std::string line_header;
    RGBColor reflective = RGBColor();
    input_file >> reflective;
    return new Reflective(reflective);
}

void SceneBuilder::unloadScene() {
    Scene::destroyInstance();
}