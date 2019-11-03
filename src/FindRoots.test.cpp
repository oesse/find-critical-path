#include "FindRoots.hpp"

#include <catch2/catch.hpp>

#include "TopologicalSort.hpp"

using Catch::Matchers::UnorderedEquals;

TEST_CASE("root nodes do not have any in edges") {
  Graph g;
  g.addEdge(0, 1); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(0, 2); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(1, 3); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(1, 2); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(2, 4); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(2, 5); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(2, 3); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(3, 5); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(3, 4); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(4, 5); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(6, 2); // NOLINT cppcoreguidelines-avoid-magic-numbers

  auto topOrder = topologicalSort(g);
  auto roots = findRoots(g, topOrder);

  // NOLINTNEXTLINE cppcoreguidelines-avoid-magic-numbers
  NodeList expectedRoots{0, 6};
  REQUIRE_THAT(roots, UnorderedEquals(expectedRoots));
}
