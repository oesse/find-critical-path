cmake_minimum_required(VERSION 3.12)
project(CriticialPathFinder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Graph OBJECT)
target_sources(Graph PRIVATE
  FindCriticalPath.cpp
  FindRoots.cpp
  Graph.cpp
  TopologicalSort.cpp
  WeightedGraph.cpp
)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Graph)

