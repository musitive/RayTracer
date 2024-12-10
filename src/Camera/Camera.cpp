#include "Camera.h"
#include "Scene.h"
#include <numeric>
#include <random>

Camera::Camera(const int& width, const int& height, const Point3D& look_at,
               const Point3D& look_from, const Point3D& up, const double& fov) {
    this->width = width;
    this->height = height;
    this->look_at = look_at;
    this->look_from = look_from;
    this->up = up;
    view_angle = calculateViewAngle(fov);
    aspect_ratio = static_cast<double>(width) / height;
}

Camera::~Camera() {}

Ray Camera::computeRay(const double &x, const double &y) {
    double viewport_x = calculateViewportX(x);
    double viewport_y = calculateViewportY(y);

    Point3D look_at_shifted = Point3D(viewport_x, viewport_y, 0) + look_at;

    Ray ray = Ray(look_from, look_at_shifted);
    return ray;
}

double Camera::calculateViewAngle(const double &fov) const {
    double angle_radians = M_PI * 0.5 * fov;
    return tan(angle_radians / 180.);
}

Frame* Camera::render() {
    RGBColor color;
    Frame* frame = new Frame(width, height);

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            color = computeColorAtPixel(x, y);
            frame->setPixel(Point2D{x, y}, color);
        }
    }

    return frame;
}

RGBColor Camera::computeColorAtPixel(int x, int y) {
    Ray r = computeRay(x, y);
    return RayTracer::trace(r, NULL, 0);
}

int Camera::getWidth() const {
    return width;
}

int Camera::getHeight() const {
    return height;
}

double Camera::calculateViewportX(const double &x) const {
    double centered_x = x + 0.5;        // 0.5 is added to center coordinates
    double normalized_x = centered_x / width;

    // Formula for viewport x-coordinate, uses aspect ratio because resolution is not square
    return (2 * normalized_x - 1) * view_angle * aspect_ratio;
}

double Camera::calculateViewportY(const double &y) const {
    double centered_y = y + 0.5;        // 0.5 is added to center coordinates
    double normalized_y = centered_y / height;

    // Formula for viewport y-coordinate, y is inverted because negative y is up
    return (1 - 2 * normalized_y) * view_angle;
}