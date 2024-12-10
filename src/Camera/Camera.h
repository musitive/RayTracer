#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include <random>
#include "Vec.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Frame.h"

/**
 * The Camera class is responsible for rendering the scene. Some of the math can get a bit complicated.
 * The formulas used to calculate the viewport were provided by Dr. Egbert in C S 455 at BYU.
 */
class Camera {
    public:
        Camera(const int &width, const int &height, const Point3D &look_at, const Point3D &look_from,
               const Point3D &up, const double &fov);
        virtual ~Camera();

        /**
         * This is the main logic for the entire program begins. 
         */
        Frame* render();
        int getWidth() const;
        int getHeight() const;

    protected:
        virtual Ray computeRay(const double &x, const double &y);

    private:
        int width, height;
        double aspect_ratio, view_angle;
        Point3D look_at, look_from, up;

        inline double calculateViewAngle(const double &fov) const;
        virtual RGBColor computeColorAtPixel(int i, int j);
        inline double calculateViewportX(const double &x) const;
        inline double calculateViewportY(const double &y) const;
};

#endif