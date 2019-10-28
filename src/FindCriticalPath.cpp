#include "FindCriticalPath.hpp"

#include <algorithm>
#include <numeric>

#include "FindRoots.hpp"
#include "TopologicalSort.hpp"

auto findCriticalPath(const WeightedGraph &g, NodeIndex targetId) -> NodeList {
  const auto topOrder = topologicalSort(g);
  const auto roots = findRoots(g, topOrder);

  std::vector<EdgeWeight> distances(g.nodeCount(),
                                    std::numeric_limits<EdgeWeight>::lowest());
  std::vector<NodeIndex> previousNodes(g.nodeCount());
  std::iota(begin(previousNodes), end(previousNodes), 0);

  for (const auto rootId : roots) {
    distances[rootId] = 0;
  }

  for (const auto nodeId : topOrder) {
    for (const auto adjacentNodeId : g.adjacentNodes(nodeId)) {
      const auto combinedDistance =
          distances[nodeId] + g.weight(nodeId, adjacentNodeId);
      if (distances[adjacentNodeId] < combinedDistance) {
        distances[adjacentNodeId] = combinedDistance;
        previousNodes[adjacentNodeId] = nodeId;
      }
    }
  }

  NodeList criticalPath{targetId};
  auto p = previousNodes[targetId];
  while (true) {
    auto pp = previousNodes[p];
    if (pp == p) {
      break;
    }
    p = pp;
    criticalPath.push_back(p);
  }
  std::reverse(begin(criticalPath), end(criticalPath));
  return criticalPath;
}
