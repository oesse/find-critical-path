add_library(Graph OBJECT)
target_sources(Graph PRIVATE
  FindCriticalPath.cpp
  FindRoots.cpp
  Graph.cpp
  TopologicalSort.cpp
  WeightedGraph.cpp
  LabeledGraph.cpp
)

add_library(Dot OBJECT)
target_sources(Dot PRIVATE ParseDotGraph.cpp)
target_link_libraries(Dot PRIVATE Boost::boost)

add_library(Buildstats OBJECT)
target_sources(Buildstats PRIVATE Buildstats.cpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Buildstats Dot Graph)

add_executable(filesystem filesystem.cpp)
target_link_libraries(filesystem PRIVATE Buildstats)


add_test_case(Graph.test.cpp Graph)
add_test_case(TopologicalSort.test.cpp Graph)
add_test_case(FindRoots.test.cpp Graph)
add_test_case(FindCriticalPath.test.cpp Graph)

add_test_case(ParseDotGraph.test.cpp Dot)

