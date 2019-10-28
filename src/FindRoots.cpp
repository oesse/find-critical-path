#include "FindRoots.hpp"

#include <set>

auto findRoots(const Graph &g, const NodeList &topOrder) -> NodeList {
  std::set<NodeIndex> seenNodes;
  auto it = begin(topOrder);
  auto endIt = end(topOrder);
  for (; it != endIt; ++it) {
    if (seenNodes.count(*it) > 0) {
      break;
    }

    for (auto nodeId : g.adjacentNodes(*it)) {
      seenNodes.insert(nodeId);
    }
  }

  NodeList result{begin(topOrder), it};
  return result;
};
