#pragma once

#include <functional>
#include <istream>

using OnEdgeFunction = std::function<void(std::string, std::string)>;

void parseDotGraph(
    std::istream &in, OnEdgeFunction onEdge = [](const auto & /* srcId */,
                                                 const auto & /* destId */) {});
