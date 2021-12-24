#include "AStar.h"

AStarNode :: AStarNode(Point& pos_, int f_, AStarNode* parent_, const Primitive& pr_) {
    pr = pr_;
    pos = &pos_;
    f = f_;
    parent = parent_;
}

AStarNode::AStarNode(const AStarNode &other) {
    pr = other.pr;
    pos = other.pos;
    f = other.f;
    parent = other.parent;
}

AStarNode::~AStarNode() = default;

AStarNode& AStarNode::operator=(const AStarNode& other) {
    pos = other.pos;
    f = other.f;
    parent = other.parent;
}

bool operator<(const AStarNode& a, const AStarNode& b) {
    return a.f < b.f;
}

bool operator == (const AStarNode& a, const AStarNode& b) {
    return a.pos == b.pos;
}

AStarNode::AStarNode() = default;

bool Compare::operator() (AStarNode& a, AStarNode& b) {
    return a.f < b.f;
}

std::tuple<bool, AStarNode, std::priority_queue<AStarNode, std::vector<AStarNode>, Compare>, std::set<AStarNode>> AStar(Grid& grid, Robot& start, const std::function<int(int, int, int, int)>& heuristic, const std::function<int(int, int, int, int, int, int)>& tie) {
    std::set<AStarNode> closed;
    std::priority_queue<AStarNode, std::vector<AStarNode>, Compare> open; 
    
    auto* goal = new AStarNode(*(new Point(start.start->x, start.start->y)), 0, nullptr, *(new Primitive()));
    bool found = false;
    int currTime = 0;
    auto *last = new AStarNode(*(new Point(start.start->x, start.start->y)), 0, nullptr, *(new Primitive()));
    open.push(*last);
    while (!open.empty()) {
        currTime++;
        AStarNode curr = open.top();
        open.pop();
        if (closed.count(curr)) {
            continue;
        }
        closed.insert(curr);
        if (curr == *goal) {
            found = true;
            last = &curr;
            break;
        }
        std::vector<Neighbour> neighbours = grid.getNeighbours(*(new timePoint()), start);
        for (auto n : grid.getNeighbours(*(new timePoint()), start)) {
            Point p = n.p;
            Primitive pr = n.pr;
            auto* neigh = new AStarNode(p, curr.f + heuristic(p.x, p.y, curr.pos->x, curr.pos->y), &curr, pr);
            if (!closed.count(*neigh)) {
                open.push(*neigh);
            }
        }
    }
    return std::make_tuple(found, *last, open, closed);
}

std::vector<AStarNode> MakePath(AStarNode goal) {
    std::vector<AStarNode> path;
    while (goal.parent != nullptr) {
        path.push_back(goal);
        goal = *goal.parent;
    }
    path.push_back(goal);
    std::reverse(path.begin(), path.end());
    return path;    
}