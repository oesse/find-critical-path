#include "FindSinks.hpp"

auto findSinks(const Graph &g) -> NodeList {
  NodeList sinks;
  for (NodeIndex i = 0; i < g.nodeCount(); ++i) {
    if (g.adjacentNodes(i).size() == 0) {
      sinks.push_back(i);
    }
  }
  return sinks;
}
