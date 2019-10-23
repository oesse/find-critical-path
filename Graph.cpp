#include "Graph.hpp"

Graph::Graph(int V) : nodes(V) {}

void Graph::addEdge(int u, int v) { nodes[u].adjacentNodes.push_back(v); }

auto Graph::nodeCount() const -> std::size_t { return nodes.size(); }

auto Graph::adjacentNodes(NodeIndex u) const -> const NodeList & {
  assert(u < nodeCount());
  return nodes[u].adjacentNodes;
}
