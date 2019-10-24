#pragma once

#include "Graph.hpp"

// Return the topologically sorted node indices of the specified graph. This
// implementation uses Kahn’s algorithm for topological sorting, see [1].
// [1] https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm
auto topologicalSort(const Graph &g) -> NodeList;
