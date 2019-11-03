#include "TopologicalSort.hpp"

#include <catch2/catch.hpp>

TEST_CASE("directed acyclic graphs can be topologically sorted") {
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

  auto topOrder = topologicalSort(g);
  auto indexOf = [&](NodeIndex i) {
    auto it = std::find(cbegin(topOrder), cend(topOrder), i);
    return std::distance(cbegin(topOrder), it);
  };

  REQUIRE(indexOf(0) < indexOf(1));
  REQUIRE(indexOf(0) < indexOf(2));

  REQUIRE(indexOf(1) < indexOf(3));
  REQUIRE(indexOf(1) < indexOf(2));

  REQUIRE(indexOf(2) < indexOf(4));
  REQUIRE(indexOf(2) < indexOf(5));
  REQUIRE(indexOf(2) < indexOf(3));

  REQUIRE(indexOf(3) < indexOf(5));
  REQUIRE(indexOf(3) < indexOf(4));

  REQUIRE(indexOf(4) < indexOf(5));
}
