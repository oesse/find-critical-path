#include "FindCriticalPath.hpp"

#include <catch2/catch.hpp>

using Catch::Matchers::Equals;

TEST_CASE("critical path on weighted graph") {
  WeightedGraph g;
  g.addEdge(0, 1, 5);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(0, 2, 3);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(1, 3, 6);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(1, 2, 2);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(2, 4, 4);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(2, 5, 2);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(2, 3, 7);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(3, 5, 1);  // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(3, 4, -1); // NOLINT cppcoreguidelines-avoid-magic-numbers
  g.addEdge(4, 5, -2); // NOLINT cppcoreguidelines-avoid-magic-numbers

  const auto targetId = 5;
  auto criticalPath = findCriticalPath(g, targetId);

  // NOLINTNEXTLINE cppcoreguidelines-avoid-magic-numbers
  NodeList expectedPath{0, 1, 2, 5};
  REQUIRE_THAT(criticalPath, Equals(expectedPath));
}
