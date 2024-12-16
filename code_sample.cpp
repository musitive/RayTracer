/**
 * My name is Dallin Frank. I'm a software engineer with a passion for computer graphics. For my code sample,
 * I wanted to demonstrate my ability to write clean code and my strong understanding of 3D math and computer graphics,
 * and algorithms. To do this, I showcase a ray tracer that I built from scratch at Brigham Young University and have 
 * been continuing to work on in my free time.
 * 
 * Earlier this year, I read through Robert C. Martin's "Clean Code" and have strived to apply those principles to 
 * my code. I've done the best I can to provide comments and documentation for the code below, but I am a strong
 * believer in self-documenting code.
 * 
 * There are missing modules, and I needed to condense everything into a single file under 1000 lines. So you won't be
 * able to run it yourself. But I will include sample images in the portfolio submission.
 */

// MAIN.CPP ============================================================================================================
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>

int main(int argc, char **argv) {
    srand(time(0));     // Create seed for the random number generator
    char *input_filename = argv[1];
    char *output_filename = argv[2];

    // I'm not including the SceneBuilder, Frame, or PPM classes, but they should be self evident
    SceneBuilder::loadScene(input_filename);

    Scene *scene = Scene::getInstance();
    Frame *frame = scene->render();

    PPM::writeToFile(output_filename, frame);

    free(frame);
    SceneBuilder::unloadScene();

    return 0;
}

// SCENE ===============================================================================================================
/**
 * @class Scene
 * @brief The Scene class is a Singleton that holds all of the actors in a scene. While Singletons can be controversial,
 * I chose to use one here because there should only ever be one scene in the program. Plus, it seems like the cleanest
 * way to handle what are essentially global variables. If this were a game engine, mutexes could be implemented to
 * ensure thread safety. Getters and setters are omitted for brevity.
 */
class Scene {
    public:
        // Creates the Singleton instance of the Scene class. For my purposes, only one scene will ever be created.
        static Scene* createInstance(const Light &light, const RGBColor &global,
            const RGBColor &background, Camera *cam)
        {
            instance = new Scene(light, global, background, cam);
            return instance;
        }

        static void destroyInstance() {
            if (instance) {
                delete instance;
                instance = nullptr;
            }
        }

        static Scene* getInstance() {
            if (!instance) throw std::invalid_argument("Scene instance does not exist");
            return instance;
        }

        Frame* render() { return cam->render(); }

        // The copy constructor and assignment operator must be deleted to prevent copying the Singleton instance
        Scene(const Scene&) = delete;
        Scene &operator=(const Scene&) = delete;

    private:
        static Scene* instance;

        Light light;                // For now, the single light source in the scene
        RGBColor global;            // Global illumination
        RGBColor background;
        std::vector<AbstractObject*> actors; // All objects in the scene
        Camera* cam;

        // Constructor and destructor are private to prevent instantiation outside of the class. Removed for brevity
        Scene(const Light &light, const RGBColor &global, const RGBColor &background, Camera *cam);
        ~Scene();
};

// CAMERA ==============================================================================================================
constexpr double DEG_TO_RAD_CONSTANT = M_PI / 180.0;
#define DEG_TO_RAD(x) (x * DEG_TO_RAD_CONSTANT)

/**
 * @class Camera
 * @brief The Camera class is responsible for rendering the scene. The formulas used to calculate the viewport were
 * provided by Dr. Egbert in C S 455 at BYU.
 */
class Camera {
    public:
        Camera(const int &width, const int &height, const vec3 &look_at,
            const vec3 &look_from, const vec3 &up, const double &field_of_view)
        {
            // Member variable assignments skipped for brevity, except for the following
            view_angle = calculateViewAngle(field_of_view);
            aspect_ratio = static_cast<double>(width) / height; 
        }

        Frame *render() {
            RGBColor color;
            Frame *frame = new Frame(width, height);

            // Calculate the color of each pixel in the frame
            for(int y = 0; y < height; ++y) {
                for(int x = 0; x < width; ++x) {
                    color = computeColorAtPixel(x, y);
                    frame->setPixel(x, y, color);
                }
            }

            return frame;
        }

    protected:
        /**
         * @brief This method calculates the view angle taking the tangent of half the field of view (in radians).
         * @param field_of_view The field of view in degrees.
         */
        inline double calculateViewAngle(const double &field_of_view) const {
            double fov_angle_radians = DEG_TO_RAD(field_of_view) * 0.5;  
            return tan(fov_angle_radians);
        }

        // Casts a ray through the scene and returns the color of the object it intersects
        virtual RGBColor computeColorAtPixel(const int &x, const int &y) {
            Ray ray = computeRay(x, y);
            return RayTracer::trace(ray);
        }

        // Creates a ray from the camera origin to the viewport
        virtual Ray computeRay(const double &x, const double &y) {
            double viewport_x = calculateViewportX(x);
            double viewport_y = calculateViewportY(y);
            vec3 offset = vec3(viewport_x, viewport_y, 0);

            vec3 look_at_shifted = look_at + offset;
            return Ray(look_from, look_at_shifted);
        }

        // Projects the viewport x-coordinate into the scene
        inline double calculateViewportX(const double &x) const {
            double centered_x = x + 0.5;        // 0.5 is added to center coordinates
            double normalized_x = centered_x / width;

            // Formula for viewport x-coordinate, uses aspect ratio because resolution is not square
            return (2 * normalized_x - 1) * view_angle * aspect_ratio;
        }

        // Projects the viewport y-coordinate into the scene
        inline double calculateViewportY(const double &y) const {
            double centered_y = y + 0.5;        // 0.5 is added to center coordinates
            double normalized_y = centered_y / height;

            // Formula for viewport y-coordinate, y is inverted because negative y is up
            return (1 - 2 * normalized_y) * view_angle;
        }

        int width, height;
        double aspect_ratio, view_angle;
        vec3 look_at, look_from, up;
};

// ANTI-ALIASING =======================================================================================================
/**
 * @class AntiAliasCam
 * @brief I wanted to this class because it showcases some of the extended learning I did at BYU. The class is an
 * extension of the Camera class that adds anti-aliasing, based on a research paper that I borrowed from Dr. Egbert.
 * I no longer have access to the paper, and I don't remember the author's name; please note that the code is my own
 * implementation of the algorithm described in the paper, but the algorithm itself is not mine.
 */
class AntiAliasCam : public Camera
{
    protected:
        int samples;                // Number of samples to take per pixel, defined in the constructor
        double inverted_samples;    // 1 / samples for efficiency

        // Overrides the base class color computation method to add anti-aliasing
        RGBColor computeColorAtPixel(const int &x, const int &y) override {
            std::vector<RGBColor> colors = std::vector<RGBColor>();
            double jittered_x, jittered_y;
            Ray ray;
            RGBColor c;

            // Cast multiple rays per pixel and average the colors
            for(int y_offset = 0; y_offset < samples; ++y_offset) {
                for(int x_offset = 0; x_offset < samples; ++x_offset) {
                    jittered_x = jitter(x + x_offset * inverted_samples);
                    jittered_y = jitter(y + y_offset * inverted_samples);
                    ray = computeRay(jittered_x, jittered_y);
                    c = RayTracer::trace(ray);
                    colors.push_back(c);
                }
            }

            return average(colors);
        }

        // Adds a random offset to the pixel coordinates to reduce aliasing
        double jitter(const int &x) const {
            std::uniform_real_distribution<double> unif(0, inverted_samples);   // uniform distribution
            std::default_random_engine re;  // random number generator
            return x + unif(re);
        }
};

// RAY TRACER ==========================================================================================================
/**
 * @class RayTracer
 * @brief The RayTracer class is a static class that contains the logic for casting rays and tracing them through the
 * scene. I opted to store this logic in it's own class so that it can easily be replaced or extended in the future.
 */
class RayTracer {
    public:
        static KDTree *kd_tree;

        // This method traces a ray through the scene and returns the color of the object it intersects.
        static RGBColor trace(const Ray &ray, AbstractObject *current = nullptr, const int &depth = 0) {
            if (depth >= MAX_DEPTH) return MAX_COLOR;

            // Allocate memory for the closest intersection. This is done to avoid multiple allocations.
            // This information can't be stored on the stack since it needs to be used elsewhere. Since abstract
            // classes can't be return types in C++, I opted to use pointers to the Intersections.
            void *closest_buffer = malloc(sizeof(Reflection));
            Light light = Scene::getInstance()->getLight();

            AbstractIntersect *i = findClosestIntersection(ray, current, closest_buffer);
            RGBColor color = i->computeColor(light, depth);

            free(closest_buffer);
            return color;
        }

        // Determines if an object is blocked from a light source by another object
        static bool isObjectBlocked(const vec3 &light_position, const vec3 &hit_point, const AbstractObject *current) {
            Ray shadow_ray(hit_point, light_position - hit_point);
            return kd_tree->isObjectBlocked(shadow_ray, current);
        }   

    private:
        static const int MAX_DEPTH = 3;     // Maximum depth of recursion, should be set in the SceneBuilder

        // This method finds the closest intersection of a ray with an object in the scene, using a KD tree to
        // reduce the number of intersection tests in more complex scenes.
        static AbstractIntersect *findClosestIntersection(const Ray &ray, AbstractObject *reflected_object,
            void *closest_buffer)
        {
            void *current_buffer = malloc(sizeof(Reflection));

            IntersectionFactory::createMissed(current_buffer);
            AbstractIntersect *closest = kd_tree->findClosestIntersection(ray, closest_buffer, current_buffer);

            free(current_buffer);
            return closest;
        }
};

// KD TREE =============================================================================================================
#define DIMENSIONS 3
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2        // @todo: Replace with an enum

/**
 * @class KDTreeNode
 * @brief The KDTreeNode class is a node in the KD tree. It contains an actor, a bounding box, and pointers to the left
 * and right children.
 */
class KDTree {
    private:
        /**
         * @struct KDTreeNode
         * @brief The KDTreeNode struct is a node in the KD tree. It contains an actor, a bounding box, and pointers
         * to the left and right nodes.
         */
        struct KDTreeNode {
            AbstractObject *obj;
            KDTreeNode *left;
            KDTreeNode *right;
            BoundingBox box;

            KDTreeNode(AbstractObject *obj) : obj(obj), left(nullptr), right(nullptr) {
                box = obj->getBoundingBox();
            }

            // Expands the bounding box of a node to include the bounding boxes of its children.
            void expandNodeBoundingBox() {
                if (left) box.expand(left->box);
                if (right) box.expand(right->box);
            }

            // Determines if a ray intersects the left bounding box of a node.
            bool doesRayIntersectLeft(const Ray &ray) const {
                return left && left->box.doesIntersect(ray);
            }

            // Determines if a ray intersects the right bounding box of a node.
            bool doesRayIntersectRight(const Ray &ray) const {
                return right && right->box.doesIntersect(ray);
            }
        };

        KDTreeNode *root;

    public:
        KDTree(std::vector<AbstractObject*> actors) {
            root = buildTree(actors, X_AXIS);
        }

        // Recursively builds the KD tree from a vector of actors, sorting them by axis at each level of the tree.
        KDTreeNode* buildTree(std::vector<AbstractObject*> &actors, const int &depth) {
            if (actors.empty()) return nullptr;     // Base case

            int axis = depth % DIMENSIONS;
            sortByAxis(actors, axis);

            // Find the median and split the actors into left and right vectors
            int median = actors.size() / 2;
            std::vector<AbstractObject*>::iterator median_it = actors.begin() + median;
            std::vector<AbstractObject*> left_actors(actors.begin(), median_it);
            std::vector<AbstractObject*> right_actors(median_it + 1, actors.end());

            // Create a new node with the median actor
            KDTreeNode* node = new KDTreeNode(actors[median]);
            node->left = buildTree(left_actors, depth + 1);
            node->right = buildTree(right_actors, depth + 1);
            node->expandNodeBoundingBox();

            return node;
        }

        // Sorts a vector of actors by the center of their bounding boxes along a specified axis.
        void sortByAxis(std::vector<AbstractObject*> &actors, const int &axis)
        {
            std::sort(actors.begin(), actors.end(),
                [axis](AbstractObject* a, AbstractObject* b)      
                {   // Lambda function to sort actors by axis
                    vec3 center_a = a->getBoundingBox().center();
                    vec3 center_b = b->getBoundingBox().center();
                    return center_a[axis] < center_b[axis];
                }
            );
        }

        // Serves as the entry point for finding the closest intersection in the KD tree.
        AbstractIntersect* findClosestIntersection(const Ray &ray, void *closest_buffer, void *current_buffer)
        {
            return findClosestIntersection(ray, closest_buffer, current_buffer, root);
        }

        /**
         * @brief Recursively finds the closest intersection of a ray in the scene, using a KD tree to reduce the
         * number of intersection tests by checking the left and right bounding boxes.
         * 
         * @param ray The ray to cast through the scene.
         * @param closest_buffer A buffer to store the closest intersection to save memory and improve efficiency.
         * @param current_buffer A buffer to store the current intersection to save memory and improve efficiency.
         * @param node The current node in the KD tree.
         * @param current_object The current object that the ray is intersecting, defaults to nullptr.
         */
        AbstractIntersect* findClosestIntersection(const Ray &ray, void *closest_buffer, void *current_buffer,
            KDTreeNode *node, AbstractObject *current_object = nullptr)
        {
            if (!node) return;      // Base case

            if (node->obj != current_object) {
                AbstractIntersect* next = IntersectionFactory::create(node->obj, ray, current_buffer);

                if (next->isCloserThan((AbstractIntersect*) closest_buffer))
                    memcpy(closest_buffer, current_buffer, sizeof(Reflection));
            }

            // Traverse the KD tree
            if (node->doesRayIntersectLeft(ray))
                findClosestIntersection(ray, closest_buffer, current_buffer, node->left, current_object);
            if (node->doesRayIntersectRight(ray))
                findClosestIntersection(ray, closest_buffer, current_buffer, node->right, current_object);
        }

        // Determines if an object is blocked from a light source by another object.
        bool isObjectBlocked(const Ray &ray, const AbstractObject *current) {
            return isObjectBlocked(ray, current, root);
        }

        // Recursively determines if an object is blocked from a light source by another object.
        bool isObjectBlocked(const Ray &ray, const AbstractObject *current, KDTreeNode *node) {
            if (!node) return false;    // Base case

            if (node->obj != current) {
                AbstractIntersect* next = IntersectionFactory::create(node->obj, ray, nullptr);
                if (next->hit_point != MISS) return true;
            }

            return isObjectBlocked(ray, current, node->left) || isObjectBlocked(ray, current, node->right);
        }
};

// BOUNDING BOX ========================================================================================================
/**
 * @struct BoundingBox
 * @brief The BoundingBox struct represents a bounding box in 3D space. It contains a minimum and maximum bound.
 */
struct BoundingBox {
    vec3 min_bound;
    vec3 max_bound;

    BoundingBox() : min_bound(INF), max_bound(-INF) {}

    // Expands the bounding box to include another bounding box.
    void expand(const BoundingBox &other)
    {
       min_bound = min(min_bound, other.min_bound);
       max_bound = max(max_bound, other.max_bound);
    }

    // Checks if a ray intersects the bounding box using the slab method.
    bool doesIntersect(const Ray &ray) const {
        double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;

        // Calculate the intersection parameters for each axis
        calculateRayPositionOnAxis(tx_min, tx_max, X_AXIS, ray);
        calculateRayPositionOnAxis(ty_min, ty_max, Y_AXIS, ray);

        // If the intervals don't overlap, the ray doesn't intersect the bounding box
        if (!intervalsOverlap(tx_min, tx_max, ty_min, ty_max)) return false;

        // Create the widest interval from the x and y intervals
        if (ty_min > tx_min) tx_min = ty_min;
        if (ty_max < tx_max) tx_max = ty_max;

        calculateRayPositionOnAxis(tz_min, tz_max, Z_AXIS, ray);        // Lazy evaluation

        // If the intervals don't overlap, the ray doesn't intersect the bounding box
        if (!intervalsOverlap(tx_min, tx_max, tz_min, tz_max)) return false;

        return true;
    }

    // Determines if two intervals overlap.
    bool intervalsOverlap(const double &min1, const double &max1, const double &min2, const double &max2) const {
        return !(min1 > max2 || min2 > max1);
    }

    // Projects a ray onto an axis to find the intersection parameters.
    void calculateRayPositionOnAxis(double &t_min, double &t_max, const int &axis, const Ray &ray) const
    {
        t_min = calculateIntersectionParameter(axis, min_bound, ray);
        t_max = calculateIntersectionParameter(axis, max_bound, ray);
        if (t_min > t_max) std::swap(t_min, t_max);
    }

    //  Calculates the intersection parameter for a ray and a bounding box.
    double calculateIntersectionParameter(const int &axis, const vec3 &bound, const Ray &ray) const {
        return (bound[axis] - ray.origin[axis]) / ray.direction[axis];
    }

    // Determines the center of the bounding box.
    vec3 center() const {
        return (min_bound + max_bound) / 2;
    }
};

// INTERSECTION FACTORY ================================================================================================
/**
 * @class IntersectionFactory
 * @brief The IntersectionFactory class is a factory class that creates intersections.
 */
class IntersectionFactory {
    public:
        /**
         * @brief This method creates an intersection based on the object and ray provided.
         * @todo: Implement a refraction class in addition to reflection and absorption
         * @return A pointer to the created intersection.
         */
        static AbstractIntersect* create(AbstractObject *obj, const Ray &ray, void *buffer)
        {
            vec3 p = obj->findIntersection(ray);

            if (p == MISS)
                return new (buffer) Miss(obj, ray);
            else if (obj->isReflective())
                return new (buffer) Reflection(obj, ray, p);
            else
                return new (buffer) Absorption(obj, ray, p);
        }

        static AbstractIntersect* createMissed(void *buffer) {
            return new (buffer) Miss();
        }
};

// INTERSECTIONS =======================================================================================================
// ALL INTERSECTION CONSTRUCTORS AND DESTRUCTORS REMOVED FOR BREVITY
/**
 * @class AbstractIntersect
 * @brief The AbstractIntersect class is an abstract class that represents an intersection of a ray with an object.
 */
class AbstractIntersect {
    public:
        // omputes the color of the intersection based on material type, light, and depth.
        // Must be overridden by subclasses.
        virtual RGBColor computeColor(const Light &light, const int &depth) const = 0;

        // Finds the distance from the intersection to a point.
        double findDistanceFromPoint(const vec3 &p) const {
            return length(hit_point - p);
        }

        // Determines if the intersection is closer than another intersection.
        bool isCloserThan(const AbstractIntersect *i) const {
            return distance < i->distance;
        }

        // Computes the normal of the actor at the intersection point.
        Direction computeActorNormal() const {
            return obj->computeNormal(hit_point);
        }

        // Determines if the intersection is blocked from a light source by another object.
        bool isBlocked(const vec3 &light_position) const {
            return RayTracer::isObjectBlocked(light_position, hit_point, obj);
        }

        // Kept public for now, but should maybe reconsider
        AbstractObject* obj;
        vec3 hit_point;
        double distance;
        Ray ray;
        Direction normal;
};

/**
 * @class Miss
 * @brief The Miss class represents a missed intersection.
 */
class Miss : public AbstractIntersect {
    public:
        // If the ray misses, the color is just the background color of the scene.
        RGBColor computeColor(const Light &light, const int &depth) const override {
            return Scene::getInstance()->getBackgroundColor();
        }
};

/**
 * @class Reflection
 * @brief The Reflection class represents an intersection with a purely reflective object.
 */
class Reflection : public AbstractIntersect {
    public:
        // Computes the color of the intersection based on the reflection of the object.
        RGBColor computeColor(const Light& light, const int& depth) const override {
            double dt = dot(ray.direction, normal);
            Direction reflect_dir = normal * (dt * 2) - ray.direction;
            Ray reflection(hit_point, -reflect_dir);

            RGBColor cd = obj->computeColor(this, light);
            RGBColor ct = RayTracer::trace(reflection, obj, depth+1);

            return ct * cd;
        }
};

/**
 * @class Absorption
 * @brief The Absorption class represents an intersection with an object that absorbs light with no reflection.
 */
class Absorption : public AbstractIntersect {
    public:
        // Computers the color without reflection.
        RGBColor computeColor(const Light& light, const int& depth) const override {
            bool blocked = isBlocked(light.position);
            return obj->computeColor(this, light, blocked);
        }
};

// ABSTRACT OBJECT =====================================================================================================
/**
 * @class AbstractObject
 * @brief An abstract class that represents an object in the scene.
 */
class AbstractObject {
    public:
        // Computes the normal of the object at a point, different for each object.
        virtual Direction computeNormal(const vec3 &p) = 0;

        // Finds the intersection of a ray with an object, different for each object.
        virtual vec3 findIntersection(const Ray &ray, const bool& culling=true) const = 0;

        // Forwards the call to the material to determine if the object is reflective.
        bool isReflective() const { return material->isReflective(); }

        // Computes the color of the object at an intersection point.
        RGBColor computeColor(const AbstractIntersect* i, const Light& light, const bool& blocked) {
            return material->computeColor(i, light, blocked);
        }

    private:
        IMaterial *material;
        BoundingBox box;
};

// SPHERE ==============================================================================================================
/**
 * @class Sphere
 * @brief The Sphere class represents a sphere in 3D space. Constructor and destructor removed for brevity.
 */
class Sphere : public AbstractObject {
    public:
        // Finds the intersection of a ray with a sphere using the geometric solution.
        vec3 findIntersection(const Ray& ray, const bool& culling=true) const override {
            vec3 to_origin = center - ray.origin;                                       // OC = S_c - r_0
            double projection_length = dot(to_origin, ray.direction);                   // tca = OC . r_d

            if (projection_length < 0) return MISS;     // the projection of OC onto the ray is behind the origin

            double distance_squared = square(to_origin) - square(projection_length);    // d^2 = ||OC||^2 - r_d^2
            double radius_squared = square(radius); 

            if (distance_squared > radius_squared) return MISS;
            
            double half_chord_length = sqrt(radius_squared - distance_squared);         // thc = sqrt(r^2 - d^2)
            double root = projection_length - half_chord_length;                        // t0 = tca - thc

            return ray.findPoint(root);
        }

        // The normal computation is simply the vector from the sphere's center to the intersection point.
        Direction computeNormal(const vec3 &p) override {
            return Direction(p, center);
        }

    private:
        vec3 center;
        double radius;
};

// TRIANGLE ============================================================================================================
/**
 * @class Triangle
 * @brief The Triangle class represents a triangle in 3D space.
 */
class Triangle : public AbstractObject {
    public:
        // Compute the normal at the time of construction to save computation time.
        Triangle(const vec3 &a, const vec3 &b, const vec3 &c) :
            v1(a), v2(b), v3(c), normal(cross_product(b-a, c-a)) {}

        // Finds the intersection of a ray with a triangle using the Moller-Trumbore algorithm.
        vec3 findIntersection(const Ray& ray, const bool& culling=true) const override {
            vec3 edge1 = v2 - v1;
            vec3 edge2 = v3 - v1;

            vec3 P = cross_product(ray.direction, edge2);                           // P = D x E2
            float determinant = dot(edge1, P);                                      // det = E1 . P

            if (culling && isParallel(determinant)) return MISS;

            float inverse_determinant = 1 / determinant;    // division is expensive, so do it once
            vec3 T = ray.origin - v1;                                               // T = r_0 - A
            double u = computeBarycentric(T, P, inverse_determinant);               // u = T . P / det

            if (isOutsideTriangle(u)) return MISS;

            vec3 Q = cross_product(T, edge1);                                       // Q = T x E1
            double v = computeBarycentric(ray.direction, Q, inverse_determinant);   // v = D . Q / det

            if (isOutsideTriangle(u, v)) return MISS;

            double intersection_distance = dot(edge2, Q) * inverse_determinant;     // t = E2 . Q / det
            return ray.findPoint(intersection_distance);
        }

        // The normal of a triangle is the same for all points on the triangle.
        Direction computeNormal(const vec3 &p) override {
            return normal;
        }

    private:
        vec3 v1, v2, v3;
        Direction normal;
        const double K_EPSILON = .000000001;

        // Computes the barycentric coordinate of a point on a triangle.
        inline double computeBarycentric(vec3 &a, vec3 &b, const double &inverse_determinant) const {
            return dot(a, b) * inverse_determinant;
        }

        // Determines if the determinant is close to zero, indicating that the ray.
        inline bool isParallel(const float &determinant) const {
            return determinant < K_EPSILON;
        }

        // the point is outside the if the barycentric coordinate is less than zero or greater than one.
        inline bool isOutsideTriangle(const double &u) const {
            return u < 0 || u > 1;
        }

        // the point is outside the if the barycentric coordinate is less than zero or greater than one.
        inline bool isOutsideTriangle(const double &u, const double &v) const {
            return v < 0 || u + v > 1;
        }
};

// MATERIALS ===========================================================================================================
/**
 * @class IMaterial
 * @brief The IMaterial class is an interface for materials in the scene.
 */
class IMaterial {
    public:
        virtual bool isReflective() { return false; }
        virtual RGBColor computeColor(const AbstractIntersect *i, const Light &light, const bool &blocked) = 0;
};

/**
 * @class Reflective
 * @brief The Reflective class represents a reflective material. Constructor removed for brevity.
 */
class Reflective : public IMaterial {
    public:
        // For now, the material is just a constant color, and the reflection intersection is more important.
        RGBColor computeColor(const AbstractIntersect *i, const Light &light, const bool &blocked) override {
            return clamp(reflective);
        }

    private:
        const RGBColor reflective;
};

/**
 * @class Diffuse
 * @brief The Diffuse class represents a diffuse material. Constructor removed for brevity.
 */
class Diffuse : public IMaterial {
    public:
        // Computes the color of the object based on the light and whether it is blocked.
        RGBColor computeColor(const AbstractIntersect *i, const Light &light, const bool &blocked) override {
            if (blocked) return computeBlockedColor();
            else return computeColorFromLight(i, light);
        }

    private:
        const RGBColor diffuse_constant, specular_constant;
        const double phong_constant;

        // Computes the color of the object when it is blocked from the light.
        RGBColor computeBlockedColor() {
            RGBColor ambient_lighting = Scene::getInstance()->getGlobalIllumination();
            return clamp(diffuse_constant * ambient_lighting);
        }

        // Computes the color of the object when it is illuminated by a light source.
        RGBColor computeColorFromLight(const AbstractIntersect* i, const Light& light) {   
            Direction to_light = Direction(light.position, i->hit_point);
            double diffuse_intensity = dot(to_light, i->computeActorNormal());

            RGBColor diffuse = computeDiffuseColor(light.color, diffuse_intensity);
            RGBColor specular = computeSpecularColor(i, light.color, diffuse_intensity, to_light);

            return clamp(diffuse + specular);
        }

        // Computes the diffuse portion of the color.
        RGBColor computeDiffuseColor(const RGBColor& light_color, const double& diffuse_intensity) const {
            RGBColor diffuse_lighting = light_color * max(0.0, diffuse_intensity);
            RGBColor ambient_lighting = Scene::getInstance()->getGlobalIllumination();

            return diffuse_constant * (ambient_lighting + diffuse_lighting);
        }

        // Computes the specular portion of the color.
        RGBColor computeSpecularColor(const AbstractIntersect* i, const RGBColor& light_color,
            const double& diffuse_intensity, const Direction& to_light) const
        {
            Direction view = Direction(i->ray.origin, i->hit_point);
            Direction light_reflection = Direction(i->normal * (diffuse_intensity * 2), to_light);

            double specular_intensity = std::max(0.0, dot(view, light_reflection));
            double specular_component = pow(specular_intensity, phong_constant);

            return light_color * specular_constant * specular_component;
        }
};

// RT LIBRARY ==========================================================================================================
/**
 * @struct Ray
 * @brief The Ray class represents a ray in 3D space. Constructor and destructor removed for brevity.
 */
struct Ray {
    vec3 origin;            // r_0
    Direction direction;    // r_d

    // Finds a point along the ray at a specified distance.
    vec3 Ray::findPoint(const double &distance) const {
        return origin + direction * distance;
    }
};

/**
 * @struct Light
 * @brief The Light struct represents a light source in the scene.
 */
struct Light {
    RGBColor color;
    vec3 position;
};

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

/**
 * @class Direction
 * @brief The Direction class is a subclass of vec3 that represents a direction vector in 3D space
 */
class Direction : public vec3 {
    public:
        // Constructor normalizes the vector
        Direction(const vec3 &from, const vec3 &to = vec3(0)) {
            vec3 d = from - to;
            d = normalize(d);
            x = d.x, y = d.y, z = d.z;
        }

        // Conversion operator to vec3
        operator vec3() const { return vec3(x, y, z); }
};

typedef vec3 RGBColor;

// GLOBAL CONSTANTS ====================================================================================================
const double INF = std::numeric_limits<double>::infinity();
const vec3 MISS = vec3(INF);

const double MIN_COLOR = 0.0;
const double MAX_COLOR = 1.0;

const RGBColor MAX_RGB = RGBColor(MAX_COLOR);

// LIBRARY FUNCTIONS ===================================================================================================
// Calculates the square of a number by multiplying it by itself for efficiency.
inline double square(const double &x) {
    return x * x;
}

// Calculates the square of a vector by taking the dot product of the vector with itself.
inline double square(const vec3 &v) {
    return dot(v, v);
}

// Calculates the length of a vector by taking the square root of the square of the vector.
double length(const vec3 &v) {
    return sqrt(square(v));
}

// Normalizes a vector by dividing it by its length.
vec3 normalize(const vec3 &v) {
    double len = length(v);

    if (len != 0) return v / len;
    else return v;
}

// Calculates the dot product of two vectors.
inline double dot(const vec3 &a, const vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Calculates the cross product of two vectors.
inline vec3 cross_product(const vec3 &a, const vec3 &b) {
    return vec3(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

// Returns a vector with the minimum components of two vectors.
vec3 min(const vec3 &a, const vec3 &b) {
    return vec3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

// Returns a vector with the maximum components of two vectors.
vec3 max(const vec3 &a, const vec3 &b) {
    return vec3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

// Clamps a color to the minimum and maximum color values.
inline RGBColor clamp(const RGBColor &v, const double &min = MIN_COLOR, const double &max = MAX_COLOR) {
    return RGBColor(std::clamp(v.x, min, max), std::clamp(v.y, min, max), std::clamp(v.z, min, max));
}

// Adds a vector of colors together and returns the average color.
RGBColor average(std::vector<RGBColor> v) {
    RGBColor t = RGBColor();
    for(RGBColor c: v) {
        t = t + c;
    }
    return t / v.size();
}
