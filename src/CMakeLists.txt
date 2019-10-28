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


add_test_case(Graph.test.cpp Graph)
add_test_case(TopologicalSort.test.cpp Graph)
add_test_case(FindRoots.test.cpp Graph)
add_test_case(FindCriticalPath.test.cpp Graph)
