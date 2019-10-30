#include "DotParser.hpp"

#include <catch2/catch.hpp>

#include <sstream>

TEST_CASE("graph with single node") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" [label=\"foogoao\"]\n"
                       "}"};
  DotParser parser{in};

  REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("graph with multiple nodes") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" [label=\"foogoao\"]\n"
                       "\"Boo\" [label=\"fooboao\"]\n"
                       "}"};
  DotParser parser{in};

  REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("graph with single edge") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" -> \"Foo\"\n"
                       "}"};
  DotParser parser{in};

  REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("graph with multiple edges") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" -> \"Foo\"\n"
                       "\"Boo\" -> \"Foo\"\n"
                       "}"};
  DotParser parser{in};

  REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("graph with node and edge") {
  std::stringstream in{"digraph depends {\n"
                       "\"Goo\" [label=\"foogoao\"]\n"
                       "\"Boo\" -> \"Foo\"\n"
                       "}"};
  DotParser parser{in};

  REQUIRE_NOTHROW(parser.parse());
}

TEST_CASE("empty graph") {
  std::stringstream in{"digraph depends {}"};
  DotParser parser{in};

  REQUIRE_NOTHROW(parser.parse());
}
