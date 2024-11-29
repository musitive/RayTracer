#include "Parser.h"

Parser::Parser() {
    scene = new Scene();
}

Scene* Parser::createEnvironmentFromFile(const string& fileName) {
    input_file.open(fileName, ios::in);

    parseCamera();
    parseSceneLighting();
    parseObjectsInScene();

    input_file.close();
    return scene;
}

void Parser::parseCamera() {
    double width, height, fov;
    Position at, from, up;
    Camera* camera;

    width = parseLabeledDouble();
    height = parseLabeledDouble();
    at = parseLabeledPosition();
    from = parseLabeledPosition();
    up = parseLabeledPosition();
    fov = parseLabeledDouble();

    camera = new Camera(width, height, at, from, up, fov);

    scene->setCamera(camera);
}

Position Parser::parseLabeledPosition() {
    double x, y, z;
    input_file >> x >> y >> z;
    return Position(x, y, z);
}

Colord Parser::parseLabeledColord() {
    double r, g, b;
    input_file >> r >> g >> b;
    return Colord(r, g, b);
}

double Parser::parseLabeledDouble() {
    double x;
    input_file >> current_label >> x;
    return x;
}

void Parser::parseSceneLighting() {
    LightSource light_source = { parseLabeledPosition(), parseLabeledColord() };

    scene->setLightSource(light_source);
    scene->setAmbientLight(parseLabeledColord());
    scene->setBackgroundColor(parseLabeledColord());
}

void Parser::parseObjectsInScene() {
    Object* object;

    input_file >> current_label;
    while(!input_file.eof()) {
        object = createObject();
        scene->addObject(object);
        input_file >> current_label;
    }
}

Object* Parser::createObject() {
    Object* object;
    Material* material;

    if (current_label == "Sphere") {
        object = createSphere();
    }
    else if (current_label == "Triangle") {
        object = createTriangle();
    }

    material = createMaterial();
    object->setMaterial(material);

    return object;
}

Object* Parser::createTriangle() {
    Position vertex1 = parseLabeledPosition();
    Position vertex2 = parseLabeledPosition();
    Position vertex3 = parseLabeledPosition();

    return new Triangle(vertex1, vertex2, vertex3);
}

Object* Parser::createSphere() {
    Position center = parseLabeledPosition();
    double radius = parseLabeledDouble();

    return new Sphere(center, radius);
}

Material* Parser::createMaterial() {
    Material* material;

    input_file >> current_label;

    if (current_label == "Diffuse") {
        material = createDiffuseMaterial();
    }
    else if (current_label == "Reflective") {
        material = createReflectiveMaterial();
    }

    return material;
}

Material* Parser::createDiffuseMaterial() {
    Colord diffuse = parseLabeledColord();
    Colord specular = parseLabeledColord();
    double phong = parseLabeledDouble();

    return new Diffuse(diffuse, specular, phong);
}

Material* Parser::createReflectiveMaterial() {
    Colord reflective = parseLabeledColord();

    return new Reflective(reflective);
}