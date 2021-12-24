#include <../Algo/AStar.h>
#include <../Algo/Heuristic.h>

int main(int argc, char *argv[]) {
    std::string mapstr =
        ".....................##......."
        ".....................##......."
        ".....................##......."
        "...##................##......."
        "...##........##......##......."
        "...##........##......#####...."
        "...##........##......#####...."
        "...##........##..............."
        "...##........##..............."
        "...##........##..............."
        "...##........##..............."
        "...##........##..............."
        ".............##..............."
        ".............##..............."
        ".............##...............";
    Grid* grid = new Grid();
    int height = 15, width = 30;
    grid->ReadMapFromString(mapstr, width, height);
    auto* start = new Point(1, 1);
    auto* goal = new Point(13, 28);
    auto* robot = new Robot(1, 1, 0, "filename", start, goal);
    auto result = AStar(*grid, *robot, DiagonalDistance, TimeTie);
    auto path = MakePath(std::get<1>(result));
    std::cerr << 1;
}