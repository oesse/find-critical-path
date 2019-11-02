#include "Buildstats.hpp"

#include <catch2/catch.hpp>

TEST_CASE("directoryToPackageName") {
  REQUIRE("libgcc" == directoryToPackageName("libgcc-8.3.0-r0"));
  REQUIRE("glib-2.0" == directoryToPackageName("glib-2.0-1_2.58.3-r0"));
}
