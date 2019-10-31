#include <iostream>
#include <iterator>

#include "FindCriticalPath.hpp"
#include "FindRoots.hpp"
#include "Graph.hpp"
#include "ParseDotGraph.hpp"
#include "TopologicalSort.hpp"
#include "WeightedGraph.hpp"

int main() {
  Graph g;
  NodeIndex lastId = 0;
  std::unordered_map<NodeIndex, std::string> nodeLabels;
  std::unordered_map<std::string, NodeIndex> nodeIds;

  auto getNodeId = [&](const auto &label) {
    auto it = nodeIds.find(label);
    if (it != end(nodeIds)) {
      return it->second;
    }

    nodeIds.insert({label, lastId});
    nodeLabels.insert({lastId, label});
    return lastId++;
  };

  auto onEdge = [&](const auto &srcId, const auto &destId) {
    const auto srcNodeId = getNodeId(srcId);
    const auto destNodeId = getNodeId(destId);
    g.addEdge(srcNodeId, destNodeId);
  };
  parseDotGraph(std::cin, onEdge);

  std::cout << "node count: " << g.nodeCount() << '\n';

  auto topOrder = topologicalSort(g);
  auto roots = findRoots(g, topOrder);

  auto toLabel = [&](NodeIndex i) { return nodeLabels.find(i)->second; };

  std::cout << "=================\n"
            << "topological order\n"
            << "=================\n";

  std::transform(begin(topOrder), end(topOrder),
                 std::ostream_iterator<std::string>{std::cout, "\n"}, toLabel);
  std::cout << '\n';

  std::cout << "=====\n"
            << "roots\n"
            << "=====\n";

  std::transform(begin(roots), end(roots),
                 std::ostream_iterator<std::string>{std::cout, "\n"}, toLabel);
  std::cout << '\n';

  return 0;
}
