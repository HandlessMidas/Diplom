#pragma once

#include <iostream>
#include <queue>
#include <Robot.h>
#include <../Grid/Grid.h>
#include <functional>
#include <set>
#include <queue>
#include <tuple>
#include <algorithm>

class AStarNode {
    public:
        Point *pos{};
        int f{};
        AStarNode* parent{};
        Primitive pr;

        AStarNode();
        AStarNode(Point &pos, int f, AStarNode* parent, const Primitive& pr);
        AStarNode(const AStarNode &other);
        ~AStarNode();

        AStarNode& operator=(const AStarNode& other);

        friend bool operator < (const AStarNode &a, const AStarNode &b);
        friend bool operator == (const AStarNode &a, const AStarNode &b);
};

class Compare {
    public:
        bool operator() (AStarNode &a, AStarNode &b);
};

std::tuple<bool, AStarNode, std::priority_queue<AStarNode, std::vector<AStarNode>, Compare>, std::set<AStarNode>> AStar(Grid& grid, Robot& start, const std::function<int(int, int, int, int)>& heuristic, const std::function<int(int, int, int, int, int, int)>& tie);

std::vector<AStarNode> MakePath(AStarNode goal);