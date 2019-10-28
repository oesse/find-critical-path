#include "FindCriticalPath.hpp"

#include <catch2/catch.hpp>

using Catch::Matchers::Equals;

TEST_CASE("critical path on weighted graph") {
  WeightedGraph g;
  g.addEdge(0, 1, 5);
  g.addEdge(0, 2, 3);
  g.addEdge(1, 3, 6);
  g.addEdge(1, 2, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 3, 7);
  g.addEdge(3, 5, 1);
  g.addEdge(3, 4, -1);
  g.addEdge(4, 5, -2);

  auto criticalPath = findCriticalPath(g, 5);
  NodeList expectedPath{0, 1, 2, 5};
  REQUIRE_THAT(criticalPath, Equals(expectedPath));
}
