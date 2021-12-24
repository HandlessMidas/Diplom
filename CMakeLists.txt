cmake_minimum_required(VERSION 3.21)
project(Diplom)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/Algo)
include_directories(src/Grid)

add_executable(Diplom
        src/Algo/Astar.cpp
        src/Algo/AStar.h
        src/Algo/Heuristic.cpp
        src/Algo/Heuristic.h
        src/Algo/Robot.cpp
        src/Algo/Robot.h
        src/Grid/Grid.cpp
        src/Grid/Grid.h
        src/Grid/Point.cpp
        src/Grid/Point.h
        src/main.cpp
        src/test.cpp)
