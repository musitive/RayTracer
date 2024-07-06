#include "Camera.h"

Camera::Camera(double width, double height, Position at, Position from, Position up, double fov) {
    this->width = width;
    this->height = height;
    this->at = at;
    this->from = from;
    this->up = up;
    this->fov = fov;
}

double Camera::getWidth() {
    return width;
}

double Camera::getHeight() {
    return height;
}