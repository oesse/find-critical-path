cmake_minimum_required(VERSION 3.12)
project(CriticialPathFinder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Graph Graph.cpp)
add_library(TopologicalSort TopologicalSort.cpp)
add_library(FindRoots FindRoots.cpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Graph TopologicalSort FindRoots)
