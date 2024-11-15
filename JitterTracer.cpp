#include "JitterTracer.h"

double JitterTracer::jitter(int i, double scale) {
    uniform_real_distribution<double> unif(0, scale);
    default_random_engine re;
    return i + unif(re);
}

Ray JitterTracer::jitter(Ray ray) {
    uniform_real_distribution<double> unif(0,0.1);
    default_random_engine re;
    ray.direction = Direction(Position(ray.direction.x+unif(re),ray.direction.y+unif(re),ray.direction.z+unif(re)));
    return ray;
}

vector<Colori> JitterTracer::subdivide(int i, int j, double scale, double angle, double aspectratio, Environment* env) {
    vector<Colori> colors = vector<Colori>();
    for(int y = 0; y < scale; ++y) {
        for(int x = 0; x < scale; ++x) {
            double first = jitter(i, 1 / scale) + x / scale;
            double second = jitter(j, 1 / scale) + y / scale;
            Ray r = computeRay(first, second, angle, aspectratio, env);
            Colori c = trace(r, env, NULL, 0);
            colors.push_back(c);
        }
    }
    return colors;
}