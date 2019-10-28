#include "Graph.hpp"

#include <catch2/catch.hpp>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("edges can be added to a graph") {
  Graph g;
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);
  g.addEdge(1, 3);

  NodeList expectedAdjacentNodes0{1, 2};
  REQUIRE_THAT(g.adjacentNodes(0), UnorderedEquals(expectedAdjacentNodes0));

  NodeList expectedAdjacentNodes1{2, 3};
  REQUIRE_THAT(g.adjacentNodes(1), UnorderedEquals(expectedAdjacentNodes1));

  REQUIRE(g.nodeCount() == 4);
}
