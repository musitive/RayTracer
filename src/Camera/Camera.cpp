#include "Camera.h"
#include "Scene.h"
#include <numeric>
#include <random>

constexpr double DEG_TO_RAD_CONSTANT = M_PI / 180.0;
#define DEG_TO_RAD(x) (x * DEG_TO_RAD_CONSTANT)

Camera::Camera(const int &width, const int &height, const vec3 &look_at,
    const vec3 &look_from, const vec3 &up, const double &field_of_view) :
    width(width), height(height), look_at(look_at), look_from(look_from), up(up)
{
    // Member variable assignments skipped for brevity, except for the following
    view_angle = calculateViewAngle(field_of_view);
    aspect_ratio = static_cast<double>(width) / height; 
}

Frame* Camera::render() {
    RGBColor color;
    Frame *frame = new Frame(width, height);

    // Calculate the color of each pixel in the frame
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            color = computeColorAtPixel(x, y);
            frame->setPixel(Point2D{x, y}, color);
        }
    }

    return frame;
}

inline double Camera::calculateViewAngle(const double &field_of_view) const {
    double fov_angle_radians = DEG_TO_RAD(field_of_view) * 0.5;  
    return tan(fov_angle_radians);
}

// Casts a ray through the scene and returns the color of the object it intersects
RGBColor Camera::computeColorAtPixel(const int &x, const int &y) {
    Ray ray = computeRay(x, y);
    return RayTracer::trace(ray);
}

// Creates a ray from the camera origin to the viewport
Ray Camera::computeRay(const double &x, const double &y) {
    double viewport_x = calculateViewportX(x);
    double viewport_y = calculateViewportY(y);
    vec3 offset = vec3(viewport_x, viewport_y, 0);

    vec3 look_at_shifted = look_at + offset;
    return Ray(look_from, look_at_shifted);
}

// Projects the viewport x-coordinate into the scene
inline double Camera::calculateViewportX(const double &x) const {
    double centered_x = x + 0.5;        // 0.5 is added to center coordinates
    double normalized_x = centered_x / width;

    // Formula for viewport x-coordinate, uses aspect ratio because resolution is not square
    return (2 * normalized_x - 1) * view_angle * aspect_ratio;
}

// Projects the viewport y-coordinate into the scene
inline double Camera::calculateViewportY(const double &y) const {
    double centered_y = y + 0.5;        // 0.5 is added to center coordinates
    double normalized_y = centered_y / height;

    // Formula for viewport y-coordinate, y is inverted because negative y is up
    return (1 - 2 * normalized_y) * view_angle;
}