#pragma once

#include <vector>
#include <string>
#include <../Algo/Robot.h>
#include <cmath>

class Neighbour {
    public:
        Neighbour();
        Neighbour(const Neighbour& other);
        Neighbour(const Primitive& pr, const Point& p);
        ~Neighbour();
        Primitive pr;
        Point p;
};

class Grid {
    public:
        Grid();
        Grid(const std::string& filename);
        ~Grid();

        int width;
        int height;
        std::vector<std::vector<bool>> grid;

        void ReadMapFromString(const std::string& strMap, int width, int height);
        bool isFree(Point& point);
        std::vector< Neighbour > getNeighbours(timePoint& point, Robot& robot);
};