#include "Robot.h"

Primitive::Primitive() {
    type = "";
    l = -1;
    r = -1;
    angle = 0;
    direction = 1;
}

Primitive::Primitive(std::string type_, double angle_, double l_, double r_, int direction_) {
    direction = direction_;
    type = std::move(type_);
    angle = angle_ * M_PI / 180.0;
    l = l_;
    r = r_;
}

Primitive::Primitive(const Primitive &other) {
    direction = other.direction;
    type = other.type;
    angle = other.angle;
    l = other.l;
    r = other.r;
}

Primitive::~Primitive() = default;

Robot :: Robot(int length_, int width_, int angle_, const std::string& filename_, Point* start_, Point* goal_) {
    length = length_;
    width = width_;
    angle = angle_;
    setPrimitivesFromFile(filename_);
    start = new timePoint(*start_);
    goal = goal_;
    primitives.resize(8);
}

Robot :: ~Robot() {
    delete this->start;
    delete this->goal;
}

void Robot :: setPrimitivesFromFile(const std::string& filename) {
    std::ifstream in;
    in.open(filename, std::ios::in);
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string type;
        double r, l, angle_;
        int direction;
        ss >> type >> direction;
        if (line.rfind("Arc", 0) == 0) {
            ss >> r >> angle_;
            this->primitives[primitives.size() - 1].push_back(*(new Primitive(type, angle_, -1, r, direction)));
        } else {
            if (line.rfind("Forward-turn-arc", 0) == 0) {
                ss >> l >> r >> angle_;
                this->primitives[primitives.size() - 1].push_back(*(new Primitive(type, angle_, l, r, direction)));
            } else {
                ss >> l;
                this->primitives[primitives.size() - 1].push_back(*(new Primitive(type, 0, l, -1, direction)));
            }
        }
    }
    //Primitive format: type, dx, dy, l, r
}

