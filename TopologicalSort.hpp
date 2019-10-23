#pragma once

#include "Graph.hpp"

// Return the topologically sorted node indices of the specified graph.
auto topologicalSort(const Graph &g) -> NodeList;
