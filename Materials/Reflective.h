
class Reflective : public Material {
    public:
        Colord reflective;
    public:
        Reflective(Colord reflective) : reflective(reflective) { isReflective = true; }
        Colori computeColor(Position from, Position p, Direction n, LightSource light, bool blocked, Colord ambient) override {
            return bound(reflective);
        }
};