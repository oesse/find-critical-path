add_library(Graph OBJECT)
target_sources(Graph PRIVATE
  FindCriticalPath.cpp
  FindRoots.cpp
  FindSinks.cpp
  Graph.cpp
  LabeledGraph.cpp
  TopologicalSort.cpp
  WeightedGraph.cpp
)

add_library(Dot OBJECT)
target_sources(Dot PRIVATE ParseDotGraph.cpp)
target_link_libraries(Dot PRIVATE Boost::boost)

add_library(Buildstats OBJECT)
target_sources(Buildstats PRIVATE Buildstats.cpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Buildstats Dot Graph)
set_target_properties(main PROPERTIES OUTPUT_NAME find-critical-path)

include(GNUInstallDirs)
install(TARGETS main RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_test_case(Graph.test.cpp Graph)
add_test_case(TopologicalSort.test.cpp Graph)
add_test_case(FindRoots.test.cpp Graph)
add_test_case(FindSinks.test.cpp Graph)
add_test_case(FindCriticalPath.test.cpp Graph)

add_test_case(ParseDotGraph.test.cpp Dot)

add_test_case(Buildstats.test.cpp Buildstats)
