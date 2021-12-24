#include <../Algo/AStar.h>
#include <../Algo/Heuristic.h>
#include <experimental/filesystem>

int test () {
    int length, width;
    std::cin >> length >> width;
    for (const auto& dirEntry : std::experimental::filesystem::recursive_directory_iterator("../tests/maps")) {
        Grid* grid = new Grid(dirEntry.path().filename().generic_string());
        std::ifstream in;
        in.open(dirEntry.path().filename().generic_string() + ".scen", std::ios::in);
        std::string line;
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            int num, wd, ht, startX, startY, goalX, goalY, optimal_length;
            std::string name;
            in >> num >> name >> wd >> ht >> startX >> startY >> goalX >> goalY >> optimal_length;
            Robot *robot = new Robot(length, width, 0, "../tests/Primitives.txt",
                                     new Point(startX, startY), new Point(goalX, goalY));
            auto result = AStar(*grid, *robot, DiagonalDistance, TimeTie);
            auto path = MakePath(std::get<1>(result));
            std::ofstream out;
            out.open(dirEntry.path().filename().generic_string() + ".result");
            out << dirEntry.path().filename().generic_string() << '\n';
            out << ht << ' ' << wd << '\n';
            out << startX << ' ' <<  startY << '\n';
            out << goalX << ' ' << goalY << '\n';
            for (auto node : path) {
                out << node.pr.direction << ' ' << node.pr.angle << ' ' << node.pr.l << ' ' << node.pr.r << '\n';
            }
        }
    }
    return 0;
}