#include "Camera.h"
#include <numeric>
#include <random>

using namespace std;

Camera::Camera(const int& width, const int& height, const Point3D& at, const Point3D& from,
                const Point3D& up, const double& fov, Environment* env) {
    this->width = width;
    this->height = height;
    this->at = at;
    this->from = from;
    this->up = up;
    angle = calculateAngle(fov);
    aspect_ratio = static_cast<double>(width) / height;
    rt = new RayTracer(env);
}

Ray Camera::computeRay(double i, double j) {
    double xx = (2 * (i + 0.5) / width - 1) * angle * aspect_ratio;
    double yy = (1 - 2 * (j + 0.5) / height) * angle;
    // double xx = (2 * (i * 1 / width) - 1) * angle * aspect_ratio;
    // double yy = (1 - 2 * (j * 1 / height)) * angle;
    Point3D look_at = Point3D(xx,yy,0) + at;

    Ray ray = Ray(from, look_at);
    return ray;
}

double Camera::calculateAngle(double fov) {
    double angle_in_radians = M_PI * 0.5 * fov;
    return tan(angle_in_radians / 180.);
}

Frame Camera::render() {
    Frame frame = Frame(width, height);

    for(int j = 0; j < height; ++j) {
        for(int i = 0; i < width; ++i) {
            Ray r = computeRay(i, j);
            Colord c = rt->trace(r, NULL, 0);
            frame.setPixel(Point2D{i, j}, c);
        }
    }

    return frame;
}

int Camera::getWidth() const {
    return width;
}

int Camera::getHeight() const {
    return height;
}