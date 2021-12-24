#include <Heuristic.h>

int EuclidianDistance(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

int DiagonalDistance(int x1, int y1, int x2, int y2) {
    return EuclidDistance(0, 0, 1, 1) * std::min(std::abs(x1 - x2), std::abs(y1 - y2)) +
        EuclidDistance(0, 0, 0, 1) * (std::max(std::abs(x1 - x2), std::abs(y1 - y2)) - std::min(std::abs(x1 - x2), std::abs(y1 - y2)));
}

int ChebyshevDistance(int x1, int y1, int x2, int y2) {
    return std::max(std::abs(x1 - x2), std::abs(y1 - y2));
}

int EuclidDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + (pow(y1 - y2, 2)));
}

int SimpleTie (int f1, int f2, int h1, int h2, int t1, int t2) {
    return f1 < f2;
}

int HTie (int f1, int f2, int h1, int h2, int t1, int t2) {
    if (f1 == f2) {
        return h1 < h2;
    }
    return f1 < f2;
}
    
int TimeTie (int f1, int f2, int h1, int h2, int t1, int t2) {
    if (f1 == f2) {
        if (h1 == h2) {
            return t1 > t2;
        }
        return h1 < h2;
    }
    return f1 < f2;
}