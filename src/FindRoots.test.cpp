#include "FindRoots.hpp"

#include <catch2/catch.hpp>

#include "TopologicalSort.hpp"

using Catch::Matchers::UnorderedEquals;

TEST_CASE("root nodes do not have any in edges") {
  Graph g;
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 2);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(2, 3);
  g.addEdge(3, 5);
  g.addEdge(3, 4);
  g.addEdge(4, 5);
  g.addEdge(6, 2);

  auto topOrder = topologicalSort(g);
  auto roots = findRoots(g, topOrder);

  NodeList expectedRoots{0, 6};
  REQUIRE_THAT(roots, UnorderedEquals(expectedRoots));
}
