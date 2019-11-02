#include "FindSinks.hpp"

#include <catch2/catch.hpp>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("root nodes do not have any out edges") {
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
  g.addEdge(4, 6);

  auto sinks = findSinks(g);

  NodeList expectedRoots{5, 6};
  REQUIRE_THAT(sinks, UnorderedEquals(expectedRoots));
}
