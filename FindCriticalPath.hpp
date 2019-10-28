#pragma once

#include "WeightedGraph.hpp"

auto findCriticalPath(const WeightedGraph &g, NodeIndex target) -> NodeList;
