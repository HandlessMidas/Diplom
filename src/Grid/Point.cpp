#include <Point.h>

Point :: Point(int x, int y) : x(), y() {};

Point :: Point(Point &other) {
    this->x = other.x;
    this->y = other.y;
};

double Point :: distTo(const Point& other) const {
    return (sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2)));
}

Point::~Point() = default;

Point::Point() = default;

timePoint :: timePoint() {
    x = 0;
    y = 0;
    time = time;
}

timePoint :: timePoint(int x, int y, long long time) : Point(x, y), time() {}

timePoint :: timePoint(Point& point) {
    this->x = point.x;
    this->y = point.y;
}

Point& timePoint :: getPoint() {
    Point* res = new Point(this->x, this->y); 
    return *res;
}

timePoint::~timePoint() = default;
