#include "Grid.h"

Neighbour ::Neighbour(const Primitive& pr_, const Point& p_) {
    pr = pr_;
    p = p_;
}

Neighbour::Neighbour(const Neighbour& other) {
    pr = other.pr;
    p = other.p;
}

Neighbour::~Neighbour() = default;

Neighbour::Neighbour() = default;

Grid :: Grid(const std::string& filename) {
    std::ifstream in;
    in.open(filename, std::ios::in);
    std::string line;
    std::string strMap;
    std::getline(in, line);
    std::stringstream ss(line);
    int width_, height_;
    ss >> width_ >> height_;
    while (std::getline(in, line)) {
        strMap += line;
    }
    this->ReadMapFromString(strMap, width_, height_);   
}

void Grid :: ReadMapFromString(const std::string& strMap, int width_, int height_) {
    width = width_;
    height = height_;
    grid.resize(width, std::vector<bool> (height, true));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            char c = strMap[i * width + j];
            if (c == '.' || c == 'G') {
                this->grid[i][j] = false;
            }
        }
    }
}

bool Grid :: isFree(Point& point) {
    if (point.x < 0 || point.y < 0 || point.x > this->height || point.y > this->width) {
        return false;
    } 
    return this->grid[point.x][point.y];
}

std::vector<Neighbour> Grid :: getNeighbours(timePoint& point, Robot& robot) {
    std::vector<Neighbour> neighbours;
    for (auto pr : robot.primitives) {
        for (auto v : pr) {
            std::string type = v.type;
            double l = v.l, r = v.r, angle = v.angle;
            auto* goal = new Point();
            bool checkL = true, checkR = true;
            int ymult = (angle < 0) ? -1 : 1, xmult = v.direction;
            if (type == "Forward") {
                if (robot.angle == 0) {
                    for (int x = point.x; (xmult == 1) ? x < point.x + l + robot.length / 2 : x > point.x - l -
                                                                                                  robot.length /
                                                                                                  2; x += xmult) {
                        for (int y = point.y - robot.width / 2; y < point.y + robot.width / 2; y++) {
                            if (!isFree(*(new Point(x, y)))) {
                                checkL = false;
                            }
                        }
                    }
                    goal = new Point((xmult == 1) ? point.x + l + robot.length / 2 : point.x - l - robot.length / 2, goal->y);
                } else {
                    for (int y = point.y; (ymult == 1) ? y < point.y + l + robot.width / 2 : y > point.y - l -
                                                                                                  robot.width /
                                                                                                  2; y += ymult) {
                        for (int x = point.x - robot.length / 2; y < point.x + robot.length / 2; x++) {
                            if (!isFree(*(new Point(x, y)))) {
                                checkL = false;
                            }
                        }
                    }
                    goal = new Point(goal->x, (ymult == 1) ? point.y + l + robot.width / 2 : point.y - l - robot.width / 2);
                }
            } else {
                int xC = point.x + xmult * l, yC = point.y + ymult * r;
                for (int y = point.y; std::abs(y - r * sqrt(2 - 2 * cos(angle)) * sin(angle / 2)) > 0; y += ymult) {
                    int a = 1, b = 2 * xC, c = xC * xC - r * r + (y - yC) * (y - yC);
                    double x1 = (-b + sqrt(b * b - 4 * a * c)) / (double)(2 * a), x2 = (-b -
                            sqrt(b * b - 4 * a * c)) / (double)(2 * a);
                    int x = std::ceil(std::max(x1, x2));
                    double k1, k2, b1, b2, b3, b4;
                    k1 = -((x - xC) / (double)(y - yC));
                    b1 = yC + r*r - (b*xC) + robot.width / 2.0 * sqrt(1 / (k1 * k1) + 1);
                    b2 = yC + r*r - (b*xC) - robot.width / 2.0 * sqrt(1 / (k1 * k1) + 1);
                    k2 = -(1 / k1);
                    b3 = sqrt(k1 * k1 * (sqrt(x * x + y * y) - robot.length / 2.0) / (k1 * k1 + 1)) / k1 +
                        sqrt(k1 * k1 * (sqrt(x * x + y * y) - robot.length / 2.0) / (k1 * k1 + 1)) / k1;
                    b4 = sqrt(k1 * k1 * (sqrt(x * x + y * y) + robot.length / 2.0) / (k1 * k1 + 1)) / k1 +
                        sqrt(k1 * k1 * (sqrt(x * x + y * y) + robot.length / 2.0) / (k1 * k1 + 1)) / k1;
                    int delta = std::max(robot.length, robot.width);
                    for (int xP = x - delta; xP < x + delta; xP++) {
                        for (int yP = y - delta; yP < y + delta; yP++) {
                            if (xmult == ymult) {
                                if (y < k1 * x + b1 && y > k1 * x + b2 && y > k2 * x + b3 && y < k2 * x + b4 &&
                                !isFree(*(new Point(x, y)))) {
                                    checkR = false;
                                }
                            } else {
                                if (y > k1 * x + b1 && y < k1 * x + b2 && y < k2 * x + b3 && y > k2 * x + b4 &&
                                !isFree(*(new Point(x, y)))) {
                                    checkR = false;
                                } 
                            }
                        }
                    }
                }
                goal = new Point(goal->x + r * sqrt(2 - 2 * cos(angle)) * cos(angle / 2), goal->y + r * sqrt(2 - 2 * cos(angle)) * sin(angle / 2));
                robot.angle = (robot.angle + 1) % 2;
                if (type != "Arc") {
                    if (robot.angle == 0) {
                        for (int x = point.x; (xmult == 1) ? x < point.x + l + robot.length / 2 : x > point.x - l -
                                                                                                      robot.length /
                                                                                                      2; x += xmult) {
                            for (int y = point.y - robot.width / 2; y < point.y + robot.width / 2; y++) {
                                if (!isFree(*(new Point(x, y)))) {
                                    checkL = false;
                                }
                            }
                        }
                        goal = new Point((xmult == 1) ? point.x + l + robot.length / 2 : point.x - l - robot.length / 2, goal->y);
                    } else {
                        for (int y = point.y; (ymult == 1) ? y < point.y + l + robot.width / 2 : y > point.y - l -
                                                                                                     robot.width /
                                                                                                     2; y += ymult) {
                            for (int x = point.x - robot.length / 2; y < point.x + robot.length / 2; x++) {
                                if (!isFree(*(new Point(x, y)))) {
                                    checkL = false;
                                }
                            }
                        }
                        goal = new Point(goal->x, (ymult == 1) ? point.y + l + robot.width / 2 : point.y - l - robot.width / 2);
                    }
                }
            }
            if (checkL && checkR) {
                neighbours.push_back(*(new Neighbour(v, *goal)));
            }
        }
    }
    return neighbours;
}

Grid::~Grid() = default;

Grid::Grid() {
    width = 0;
    height = 0;
};
