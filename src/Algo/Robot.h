#pragma once

#include <iostream>
#include <vector>
#include <../Grid/Point.h>
#include <fstream>
#include <sstream>
#include <tuple>

class Primitive {
    public:
        Primitive();
        Primitive(const Primitive& other);
        Primitive(std::string type, double angle, double l, double r, int direction);
        ~Primitive();
        std::string type;
        double angle;
        int direction;
        double l;
        double r;
};

class Robot {
    public:
        Robot(int length_, int width_, int angle_, const std::string& filename, Point* start, Point* goal);
        ~Robot();

        int length;
        int width;
        int angle;
        timePoint *start;
        Point *goal;
        std::vector<std::vector<Primitive>> primitives;
    private:
        void setPrimitivesFromFile(const std::string& filename);
};