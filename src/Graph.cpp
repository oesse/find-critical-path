#include "Graph.hpp"

#include <cassert>

#include <algorithm>

namespace {

void ensureNodeCapacity(NodeMap &nodes, NodeIndex capacity) {
  if (capacity >= nodes.size()) {
    std::fill_n(std::back_inserter(nodes), capacity - nodes.size() + 1,
                NodeMap::value_type{});
  }
}

} // namespace

void Graph::addEdge(NodeIndex u, NodeIndex v) {
  ensureNodeCapacity(nodes, std::max(u, v));
  nodes[u].adjacentNodes.push_back(v);
}

auto Graph::nodeCount() const -> std::size_t { return nodes.size(); }

auto Graph::adjacentNodes(NodeIndex u) const -> const NodeList & {
  assert(u < nodeCount());
  return nodes[u].adjacentNodes;
}
