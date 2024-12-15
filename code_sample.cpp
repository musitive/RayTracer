/**
 * Hi! My name is Dallin Frank. I'm a software engineer with a passion for computer graphics.
 * For my code samples, I wanted to demonstrate my ability to write clean and efficient code
 * as well as my strong understanding of 3D math, computer graphics, and algorithms. The first
 * is an implementation of a branch and bound algorithm to solve the Traveling Salesman Problem.
 * The second is a ray tracer that I've been working on in my free time.
 * Earlier this year, I read through Robert C. Martin's "Clean Code" and have strived to apply
 * those principles to my code. For the sake of this sample, I have prioritized readability and
 * software design over performance optimizations.
*/

// TRAVELING SALESMAN PROBLEM CODE SAMPLE ========================================

// RAY TRACER CODE SAMPLE ========================================================
#include <random>

int main(int argc, char **argv) {
    char *input_filename = argv[1];
    char *output_filename = argv[2];

    srand(time(0)); // Create seed for the random number generator

    // I'm not including the SceneBuilder, Frame, or PPM classes in this code sample
    // because they mostly deal with file I/O and are not relevant to the ray tracer
    // and they should be self-evident from the context provided here.
    SceneBuilder::loadScene(input_filename);

    Scene *scene = Scene::getInstance();    // Get pointer to the Singleton instance of the Scene
    Frame *frame = scene->render();         // This is where the magic happens

    PPM::writeToFile(output_filename, frame);

    free(frame);
    SceneBuilder::unloadScene();

    return 0;
}

/**
 * The Scene class is a Singleton that holds all of the actors in the scene.
 * While Singletons can be controversial, I chose to use one here because there
 * should only ever be one scene in the program. Plus, it seems like the cleanest
 * way to handle what are essentially global variables. If this were a game engine,
 * mutexes could be implemented to ensure thread safety.
*/
class Scene {
    public:
        // For my purposes, only one scene will ever be created. If this were a
        // game engine and I swap out scenes, it could be changed here.
        static Scene* createInstance(const Light &light, const RGBColor &global,
                                     const RGBColor &background, Camera *cam) {

            instance = new Scene(light, global, background, cam);
            return instance;
        }

        // Including this to demonstrate how to destroy the Singleton instance.
        static void destroyInstance() {
            if (instance) {
                delete instance;
                instance = nullptr;
            }
        }

        // This is how other classes will get a pointer to the Singleton instance.
        static Scene* getInstance() {
            if (!instance) throw std::invalid_argument("Scene instance does not exist");
            return instance;
        }

        Frame* render() {
            return cam->render();
        }

        // This is where the getters and setters would go

        // The copy constructor and assignment operator must be deleted to
        // prevent copying the Singleton instance
        Scene(const Scene&) = delete;
        Scene &operator=(const Scene&) = delete;

    private:
        Light light;                // For now, the single light source in the scene
        RGBColor global;            // Global illumination
        RGBColor background;
        std::vector<Actor*> actors; // All objects in the scene
        Camera* cam;

        static Scene* instance;

        // Constructor and destructor are private to prevent instantiation outside of the class
        // Constructor and destructor implementations removed for brevity
        Scene(const Light &light, const RGBColor &global, const RGBColor &background, Camera *cam);
        ~Scene();
};

/**
 * The Camera class is responsible for rendering the scene. Some of the math can get a bit complicated.
 * The formulas used to calculate the viewport were provided by Dr. Egbert in C S 455 at BYU.
 */
class Camera {
    public:
        Camera(const int &width, const int &height, const Point3D &look_at,
            const Point3D &look_from, const Point3D &up,
            const double &field_of_view) {

            // Member variable assignments skipped for brevity, except for the following
            view_angle = calculateViewAngle(field_of_view);
            aspect_ratio = static_cast<double>(width) / height; 
        }

        Frame *render() {
            RGBColor c;
            Frame *frame = new Frame(width, height);

            for(int y = 0; y < height; ++y) {
                for(int x = 0; x < width; ++x) {
                    c = computeColorAtPixel(x, y);
                    frame->setPixel(x, y, c);
                }
            }

            return frame;
        }

    protected:      // Protected so that subclasses can override these methods
        // The view_angle is calculated using the field of view in degrees. The half-angle is used in the calculation.
        inline double calculateViewAngle(const double &field_of_view) const {
            double fov_angle_radians = M_PI * 0.5 * field_of_view / 180.0;  
            return tan(fov_angle_radians);
        }

        // This is where the main logic for the entire program begins! Each 2D pixel in the frame
        // is projected onto the viewport as a 3D point in the scene and a ray is cast.
        virtual RGBColor computeColorAtPixel(int x, int y) {
            Ray ray = computeRay(x, y);
            return RayTracer::trace(ray);
        }

        // Parameters x and y are the pixel coordinates on the frame. This method calculates that
        // position in 3D space and creates a ray using the camera's look_from and look_at points.
        virtual Ray computeRay(const double &x, const double &y) {
            double viewport_x = calculateViewportX(x);
            double viewport_y = calculateViewportY(y);

            Point3D look_at_shifted = Point3D(viewport_x, viewport_y, 0) + look_at;
            return Ray(look_from, look_at_shifted);
        }

        // Projects the x-coordinate of the pixel onto the viewport in the scene
        inline double calculateViewportX(const double &x) const {
            double centered_x = x + 0.5;        // 0.5 is added to center coordinates
            double normalized_x = centered_x / width;

            // Formula for viewport x-coordinate, uses aspect ratio because resolution is not square
            return (2 * normalized_x - 1) * view_angle * aspect_ratio;
        }

        // Projects the y-coordinate of the pixel onto the viewport in the scene
        inline double calculateViewportY(const double &y) const {
            double centered_y = y + 0.5;        // 0.5 is added to center coordinates
            double normalized_y = centered_y / height;

            // Formula for viewport y-coordinate, y is inverted because negative y is up
            return (1 - 2 * normalized_y) * view_angle;
        }

        int width, height;
        double aspect_ratio, view_angle;
        Point3D look_at, look_from, up;
};

/**
 * I want to show off this class. It's an extension of the Camera class that adds anti-aliasing, based on a research
 * paper that I borrowed from Dr. Egbert. I no longer have access to the paper, and I don't remember the author's name;
 * please note that the code is my own implementation of the algorithm described in the paper, but the algorithm itself
 * is not mine.
 */
class AntiAliasCam : public Camera {
    protected:
        int samples;                // Number of samples to take per pixel, defined in the constructor
        double inverted_samples;    // 1 / samples for efficiency

        // The first of the two ways that this class provides anti-aliasing is through oversampling.
        RGBColor computeColorAtPixel(int x, int y) override {
            std::vector<RGBColor> colors = std::vector<RGBColor>();
            double jittered_x, jittered_y;
            Ray r;
            RGBColor c;

            // Cast multiple rays per pixel and average the colors
            for(int y_offset = 0; y_offset < samples; ++y_offset) {
                for(int x_offset = 0; x_offset < samples; ++x_offset) {
                    jittered_x = jitter(x) + x_offset * inverted_samples;
                    jittered_y = jitter(y) + y_offset * inverted_samples;
                    r = computeRay(jittered_x, jittered_y);
                    c = RayTracer::trace(r);
                    colors.push_back(c);
                }
            }

            return average(colors);
        }

        // The second way that this class provides anti-aliasing is through jittering.
        double jitter(int x) {
            std::uniform_real_distribution<double> unif(0, inverted_samples);   // random numbers with a uniform distribution
            std::default_random_engine re;  // random number generator
            return x + unif(re);
        }
};

/**
 * The RayTracer class is a static class that contains the logic for casting rays and tracing them through the scene.
 * I opted to store this logic in it's own class so that it can easily be replaced or extended in the future.
 */
class RayTracer {
    public:
        // This is the main method of the RayTracer, being the only public method. When called, it will trace a ray
        // recursively until it reaches the maximum depth.
        static RGBColor trace(const Ray& ray, Actor* current = nullptr, const int& depth = 0) {
            if (depth >= MAX_DEPTH) return MAX_COLOR;   // Return the maximum color if the maximum depth is reached
            Light light = Scene::getInstance()->getLight();

            // Allocate memory for the closest intersection. This is done to avoid multiple allocations.
            // This information can't be stored on the stack since it needs to be used elsewhere. Since abstract
            // classes can't be return types in C++, I opted to use pointers to the Intersections.
            void* closest_buffer = malloc(sizeof(Reflection));

            AbstractIntersection* i = findClosestIntersection(ray, current, closest_buffer);
            RGBColor c = i->computeColor(light, depth);

            free(closest_buffer);
            return c;
        }

    private:
        static const int MAX_DEPTH = 3; // Maximum depth of recursion, should be set in the SceneBuilder

        static AbstractIntersection* findClosestIntersection(const Ray& ray, Actor* current, void* closest_buffer) {
            void* buffer = malloc(sizeof(Reflection));
            std::vector<Actor*> actors = Scene::getInstance()->getActors();     // Probably shouldn't be a copy
            AbstractIntersection* closest = new (closest_buffer) Miss(nullptr, Ray());
            AbstractIntersection* next;

            for (Actor* o : actors) {
                if (o == current) continue;

                next = IntersectionFactory::create(o, ray, buffer);
                if (next->isCloserThan(closest))
                    memcpy(closest_buffer, buffer, sizeof(Reflection));
            }

            free(buffer);
            return closest;
        }
};

/**
 * TODO: Comment
 */
class AbstractIntersection {
    public:
        // Constructors and destructors removed for brevity

        // This is the main method that will be overridden by subclasses.
        // Color is dependent on material type, light, and where the ray bounces.
        virtual RGBColor computeColor(const Light& light, const int& depth) const = 0;

        double findDistanceFromPoint(const Point3D& p) const {
            return length(point - p);
        }

        bool isCloserThan(const AbstractIntersection* i) const {
            return distance < i->distance;
        }

        Direction computeActorNormal() const {
            return obj->computeNormal(point);
        }

    private:
        Actor* obj;
        Point3D point;
        double distance;
        Ray ray;
        Direction normal;
};

/**
 * TODO: Comment
 */
class Miss : public AbstractIntersection {
    public:
        computeColor(const Light& light, const int& depth) const {
            return Scene::getInstance()->getGlobalIllumination();
        }
};

/**
 * TODO: Comment
 */
class Reflection : public AbstractIntersection {
    public:
        // Constructors and destructors removed for brevity
        RGBColor computeColor(const Light& light, const int& depth) const override;
};

/**
 * TODO: Comment
 */
class Absorption : public AbstractIntersection {
    public:
        RGBColor computeColor(const Light& light, const int& depth) const override;
        bool isBlocked(const Point3D& light_position) const;
};

/**
 * TODO: Comment
 */
class Actor {
    public:
        void setMaterial(IMaterial* material);
        IMaterial* getMaterial() const;

        virtual Direction computeNormal(const Point3D& p) = 0;
        virtual Point3D findIntersection(const Ray& ray, const bool& culling=true) const = 0;

        bool isBlocking(const Ray& to_light, const Point3D& light_position, const double& distance);

    private:
        IMaterial* material;
};

/**
 * TODO: Comment
 */
class Sphere : public Actor {
    public:
        Sphere(Point3D center, double radius) : center(center), radius(radius) {}
        
        Point3D findIntersection(const Ray& ray, const bool& culling=true) const override {
            // Distance between the center of the sphere and the origin of the ray
            // OC = S_c - r_0
            Vector3D to_origin = center - ray.origin;

            // tca = OC . r_d
            double projection_length = dot(to_origin, ray.direction);

            // if tca < 0, the projection of OC onto the ray is behind the origin
            if (projection_length < 0) return MISS;

            // d^2 = ||OC||^2 - r_d^2
            double distance_squared = square(to_origin) - square(projection_length);
            double radius_squared = square(radius); // r^2

            // if d^2 > r^2, the ray misses the sphere
            if (distance_squared > radius_squared) return MISS;

            // thc = sqrt(r^2 - d^2)
            double half_chord_length = sqrt(radius_squared - distance_squared);

            // t0 = tca - thc
            double root = projection_length - half_chord_length;

            // the root exists if the ray intersects the sphere
            return ray.findPoint(root);
        }

        Direction computeNormal(const Point3D& position) override {
            return Direction(position, center);
        }

    private:
        Point3D center;
        double radius;
};

/**
 * TODO: Comment
 */
class Triangle : public Actor {
    public:
        Triangle(Point3D a, Point3D b, Point3D c) : v1(a), v2(b), v3(c),
            normal(cross_product(b-a, c-a)) {}

        // Moller-Trumbore algorithm
        Point3D findIntersection(const Ray& ray, const bool& culling=true) const override {
            Point3D edge1 = v2 - v1;
            Point3D edge2 = v3 - v1;
            // Cramer's rule
            // P = D x E2
            Vector3D P = cross_product(ray.direction, edge2);

            // det = E1 . P
            float determinant = dot(edge1, P);
            if (culling && isParallel(determinant)) return MISS;

            // division is expensive, so do it once
            float inverse_determinant = 1 / determinant;

            // T = O - V1
            Vector3D T = ray.origin - v1;

            // u = T . P / det
            double u = computeBarycentricCoordinate(T, P, inverse_determinant);
            if (isOutsideTriangle(u)) return MISS;

            // Q = T x E1
            Vector3D Q = cross_product(T, edge1);

            // v = D . Q / det
            double v = computeBarycentricCoordinate(ray.direction, Q, inverse_determinant);
            if (isOutsideTriangle(u, v)) return MISS;

            // t = E2 . Q / det
            double intersection_distance = dot(edge2, Q) * inverse_determinant;
            return ray.findPoint(intersection_distance);
        }

        Direction computeNormal(const Point3D& p) override {
            return normal;
        }

    private:
        Point3D v1, v2, v3;
        Direction normal;
        const double K_EPSILON = .000000001;

        inline double computeBarycentricCoordinate(const Vector3D& a, const Vector3D& b, const double& inverse_determinant) const {
            return dot(a, b) * inverse_determinant;
        }

        inline bool isParallel(const float& determinant) const {
            return determinant < K_EPSILON;
        }

        inline bool isOutsideTriangle(const double& u) const {
            return u < 0 || u > 1;
        }

        inline bool isOutsideTriangle(const double& u, const double& v) const {
            return v < 0 || u + v > 1;
        }
};

/**
 * TODO: Comment
 */
class IMaterial {
    public:
        bool isReflective = false;
        virtual RGBColor computeColor(const AbstractIntersection* i, const Light& light, const bool& blocked) = 0;
};

/**
 * TODO: Comment
 */
class Reflective : public IMaterial {
    public:
        Reflective(RGBColor reflective);
        RGBColor computeColor(const AbstractIntersection* i, const Light& light, const bool& blocked) override;

    public:
        const RGBColor reflective;
};

/**
 * TODO: Comment
 */
class Diffuse : public IMaterial {
    public:
        Diffuse(RGBColor diffuse, RGBColor specular, double phong);
        RGBColor computeColor(const AbstractIntersection* i, const Light& light, const bool& blocked) override;

    private:
        const RGBColor diffuse_constant, specular_constant;
        const double phong_constant;
        RGBColor computeBlockedColor();
        RGBColor computeColorFromLight(const AbstractIntersection* i, const Light& light);
        inline RGBColor computeDiffuseColor(const RGBColor& light_color, const double& diffuse_intensity) const;
        inline RGBColor computeSpecularColor(const AbstractIntersection* i, const RGBColor& light_color, const double& diffuse_intensity, const Direction& to_light) const;
};

/**
 * TODO: Comment
 */
class Ray {
    public:
        Point3D origin;        // r_0
        Direction direction;    // r_d

        Ray();
        Ray(Point3D eye, Direction s);
        Point3D findPoint(double t) const;
        

    private:
    
};

/**
 * TODO: Comment
 */
template<typename T>
class Vec3 {
    public:
        T x, y, z;

        Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
        Vec3(T v) : x(v), y(v), z(v) {}
        Vec3(T u, T v, T w) : x(u), y(v), z(w) {}
        Vec3(const Vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}
};

template<typename T>
bool operator == (const Vec3<T>& a, const Vec3<T>& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<typename T>
Vec3<T> operator + (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename T>
Vec3<T> operator * (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<typename T>
Vec3<T> operator * (const Vec3<T>& a, const double& b) {
    return Vec3<T>(a.x * b, a.y * b, a.z * b);
}

template<typename T>
Vec3<T> operator / (const Vec3<T>& a, const Vec3<T>& b) {
    return Vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template<typename T>
Vec3<T> operator / (const Vec3<T>& a, const double& b) {
    double inv_b = 1 / b;
    return a * inv_b;
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& a) {
    return Vec3<T>(-a.x, -a.y, -a.z);
}

template<typename T>
ostream & operator << (ostream &os, const Vec3<T> &v) {
    os << v.x << ' ' << v.y << ' ' << v.z; 
    return os; 
}

template<typename T>
istream & operator >> (istream &is, Vec3<T> &v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

typedef Vec3<double> RGBColor;
typedef Vec3<double> Point3D;

const double MIN_COLOR = 0.0;
const double MAX_COLOR = 1.0;

class Direction : public Point3D {
    public:
        Direction(const Point3D& to, const Point3D& from);
        Direction(const Point3D& v);
};

typedef Point3D Vector3D;

template<typename T>
Vec3<T> average(vector<Vec3<T>> v) {
    Vec3<T> t = Vec3<T>();
    for(Vec3<T> c: v) {
        t = t + c;
    }
    return t / v.size();
}

double length(const Point3D& vec);
Point3D normalize(const Point3D& vec);

inline double dot(const Point3D& vec1, const Point3D& vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Point3D cross_product(const Point3D& vec1, const Point3D& vec2) {
    return Point3D(vec1.y * vec2.z - vec1.z * vec2.y,
                    vec1.z * vec2.x - vec1.x * vec2.z,
                    vec1.x * vec2.y - vec1.y * vec2.x);
}

inline RGBColor clamp(const RGBColor& v, const double& min, const double& max) {
    return RGBColor(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
}

inline double square(const double& x) {
    return x * x;
}

inline double square(const Vector3D& a) {
    return dot(a, a);
}

const double INF = std::numeric_limits<double>::infinity();
const Point3D MISS = Point3D(INF);
const RGBColor MAX_COLOR = RGBColor(1);