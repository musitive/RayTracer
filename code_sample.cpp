/**
 * Hi! My name is Dallin Frank. I'm a software engineer with a passion for computer graphics.
 * For my code samples, I wanted to demonstrate my ability to write clean and efficient code
 * as well as my strong understanding of 3D math, computer graphics, and algorithms. The first
 * code sample is a ray tracer that I've been working on in my free time. The second code sample
 * a implementation of a branch and bound algorithm to solve the Traveling Salesman Problem.
 * Earlier this year, I read through Robert C. Martin's "Clean Code" and have strived to apply
 * those principles to my code. For the sake of this sample, I have prioritized readability and
 * software design over performance optimizations.
*/

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
        // Not implementing here for brevity
        Scene(const Light &light, const RGBColor &global, const RGBColor &background, Camera *cam);
        ~Scene();
};

/**
 * The Camera class is responsible for rendering the scene. Some of the math can get a bit complicated.
 * The formulas used to calculate the viewport were provided by Dr. Egbert in C S 455 at BYU.
 */
class Camera {
    public:
        Camera(const int &width, const int &height, const Point3D &look_at, const Point3D &look_from,
               const Point3D &up, const double &field_of_view) {
            // Member variable assignments skipped for brevity, except for the following
            view_angle = calculateViewAngle(field_of_view);
            aspect_ratio = static_cast<double>(width) / height; 
        }

        Frame *render() {
            RGBColor color;
            Frame *frame = new Frame(width, height);

            for(int y = 0; y < height; ++y) {
                for(int x = 0; x < width; ++x) {
                    color = computeColorAtPixel(x, y);
                    frame->setPixel(x, y, color);
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
            Ray r = computeRay(x, y);
            return RayTracer::trace(r);     // This is where the fun begins!
        }

        // Parameters x and y are the pixel coordinates on the frame. This method calculates that position in 3D space
        // and creates a ray using the camera's look_from and look_at points.
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

// TRAVELING SALESMAN PROBLEM CODE SAMPLE ========================================