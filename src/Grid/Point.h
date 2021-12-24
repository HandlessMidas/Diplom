#pragma once

#include <vector>
#include <string>
#include <math.h>

class Point {
    public:
        Point(int x, int y);
        Point();
        Point(Point &other);
        ~Point();

        int x{};
        int y{};

        double distTo(const Point& other) const;
};

class timePoint: public Point {
    public:
        timePoint(int x, int y, long long time);
        explicit timePoint(Point& point);
        timePoint();
        ~timePoint();

        long long time = -1;
        
        Point& getPoint();
};