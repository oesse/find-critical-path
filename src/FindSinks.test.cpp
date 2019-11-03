#include "FindSinks.hpp"

#include <catch2/catch.hpp>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("root nodes do not have any out edges") {
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
  g.addEdge(4, 6); // NOLINT cppcoreguidelines-avoid-magic-numbers

  auto sinks = findSinks(g);
  // NOLINTNEXTLINE cppcoreguidelines-avoid-magic-numbers
  NodeList expectedRoots{5, 6};
  REQUIRE_THAT(sinks, UnorderedEquals(expectedRoots));
}
