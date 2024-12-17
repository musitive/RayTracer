#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

/**
 * @class vec3
 * @brief I wanted to create this class myself to better understand how vectors work in 3D space. However, for
 * future projects, I will likely stick to the standard glm::vec3 class to save time and ensure correctness.
 * It's a bit messier at this point, but I wanted to keep it in the project to show my understanding of 3D math.
 */
class vec3 {
    public:
        double x, y, z;

        // CONSTRUCTORS
        vec3() : x(double(0)), y(double(0)), z(double(0)) {}
        vec3(double v) : x(v), y(v), z(v) {}
        vec3(double u, double v, double w) : x(u), y(v), z(w) {}
        vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}

        // ACCESSORS
        const double& operator[](size_t index) const
        {
            if (index == 0) return x;
            else if (index == 1) return y;
            else if (index == 2) return z;
            throw std::out_of_range("Index out of range");
        }

        // OPERATORS
        vec3 operator - () const { return vec3(-x, -y, -z); }

        bool operator != (const vec3 &other) const { return !(*this == other); }
        bool operator == (const vec3 &other) const { return x == other.x && y == other.y && z == other.z; }
        vec3 operator + (const vec3 &other) const { return vec3(x + other.x, y + other.y, z + other.z); }
        vec3 operator - (const vec3 &other) const { return vec3(x - other.x, y - other.y, z - other.z); }
        vec3 operator * (const vec3 &other) const { return vec3(x * other.x, y * other.y, z * other.z); }
        vec3 operator / (const vec3 &other) const { return vec3(x / other.x, y / other.y, z / other.z); }

        vec3 operator * (const double &scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }
        vec3 operator / (const double &scalar) const {
            double inv_scalar = 1 / scalar;             // division is expensive, so do it once
            return vec3(x * inv_scalar, y * inv_scalar, z * inv_scalar);
        }
};

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

inline std::istream& operator>>(std::istream& is, vec3& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

typedef vec3 RGBColor;

// GLOBAL CONSTANTS ====================================================================================================
const double INF = std::numeric_limits<double>::infinity();
const vec3 MISS = vec3(INF);

const double MIN_COLOR = 0.0;
const double MAX_COLOR = 1.0;

const RGBColor MAX_RGB = RGBColor(MAX_COLOR);

// LIBRARY FUNCTIONS ===================================================================================================
// Calculates the dot product of two vectors.
inline double dot(const vec3 &a, const vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Calculates the square of a number by multiplying it by itself for efficiency.
inline double square(const double &x) {
    return x * x;
}

// Calculates the square of a vector by taking the dot product of the vector with itself.
inline double square(const vec3 &v) {
    return dot(v, v);
}

// Calculates the cross product of two vectors.
inline vec3 cross_product(const vec3 &a, const vec3 &b) {
    return vec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

// Clamps a color to the minimum and maximum color values.
inline RGBColor clamp(const RGBColor &v, const double &min = MIN_COLOR, const double &max = MAX_COLOR) {
    return RGBColor(std::clamp(v.x, min, max), std::clamp(v.y, min, max), std::clamp(v.z, min, max));
}

namespace rt_lib {
    // Calculates the length of a vector by taking the square root of the square of the vector.
    inline double length(const vec3 &v) {
        return sqrt(square(v));
    }

    // Normalizes a vector by dividing it by its length.
    inline vec3 normalize(const vec3 &v) {
        double len = length(v);

        if (len != 0) return v / len;
        else return v;
    }

    // Returns a vector with the minimum components of two vectors.
    inline vec3 min(const vec3 &a, const vec3 &b) {
        return vec3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    }

    // Returns a vector with the maximum components of two vectors.
    inline vec3 max(const vec3 &a, const vec3 &b) {
        return vec3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
    }

    // Adds a vector of colors together and returns the average color.
    inline RGBColor average(std::vector<RGBColor> v) {
        RGBColor t = RGBColor();
        for(RGBColor c: v) {
            t = t + c;
        }
        return t / v.size();
    }
}

#endif