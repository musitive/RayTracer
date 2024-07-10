#include "Material.h"

class Diffuse : public Material {
    private:
        Colord diffuse;
        Colord specular;
        double phong;
    public:
        Diffuse(Colord diffuse, Colord specular, double phong);
};