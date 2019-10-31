#include "DotParser.hpp"

#include <catch2/catch.hpp>

#include <sstream>

TEST_CASE("graph with single node") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" [label=\"foogoao\"]\n"
                       "}"};

  REQUIRE_NOTHROW(parseDotGraph(in));
}

TEST_CASE("graph with multiple nodes") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" [label=\"foogoao\"]\n"
                       "\"Boo\" [label=\"fooboao\"]\n"
                       "}"};
  REQUIRE_NOTHROW(parseDotGraph(in));
}

TEST_CASE("graph with single edge") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" -> \"Foo\"\n"
                       "}"};

  std::vector<std::pair<std::string, std::string>> edges;
  auto onEdge = [&](const auto &srcId, const auto &destId) {
    edges.push_back(std::make_pair(srcId, destId));
  };
  REQUIRE_NOTHROW(parseDotGraph(in, onEdge));

  REQUIRE(edges.size() == 1ul);
  REQUIRE(edges[0].first == "Goo");
  REQUIRE(edges[0].second == "Foo");
}

TEST_CASE("graph with multiple edges") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" -> \"Foo\"\n"
                       "\"Boo\" -> \"Foo\"\n"
                       "}"};

  std::vector<std::pair<std::string, std::string>> edges;
  auto onEdge = [&](const auto &srcId, const auto &destId) {
    edges.push_back(std::make_pair(srcId, destId));
  };
  REQUIRE_NOTHROW(parseDotGraph(in, onEdge));

  REQUIRE(edges.size() == 2ul);
  REQUIRE(edges[1].first == "Boo");
  REQUIRE(edges[1].second == "Foo");
}

TEST_CASE("graph with node and edge") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" [label=\"foogoao\"]\n"
                       "\"Boo\" -> \"Foo\"\n"
                       "}"};
  REQUIRE_NOTHROW(parseDotGraph(in));
}

TEST_CASE("empty graph") {
  std::stringstream in{"digraph depends {}"};
  REQUIRE_NOTHROW(parseDotGraph(in));
}
