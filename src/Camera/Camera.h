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
        Camera(const int &width, const int &height, const vec3 &look_at,
            const vec3 &look_from, const vec3 &up, const double &field_of_view);

        Frame *render();

        int getWidth() const { return width; }
        int getHeight() const { return height; }

    protected:
        /**
         * @brief This method calculates the view angle taking the tangent of half the field of view (in radians).
         * @param field_of_view The field of view in degrees.
         */
        inline double calculateViewAngle(const double &field_of_view) const;

        // Casts a ray through the scene and returns the color of the object it intersects
        virtual RGBColor computeColorAtPixel(const int &x, const int &y);

        // Creates a ray from the camera origin to the viewport
        virtual Ray computeRay(const double &x, const double &y);

        // Projects the viewport x-coordinate into the scene
        inline double calculateViewportX(const double &x) const;

        // Projects the viewport y-coordinate into the scene
        inline double calculateViewportY(const double &y) const;

        int width, height;
        double aspect_ratio, view_angle;
        vec3 look_at, look_from, up;
};

#endif