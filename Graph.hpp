#pragma once

#include <cassert>
#include <queue>
#include <vector>

using NodeIndex = std::size_t;
using NodeList = std::vector<NodeIndex>;

struct Node {
  NodeList adjacentNodes;
};

using NodeMap = std::vector<Node>;

class Graph {
  NodeMap nodes;

public:
  void addEdge(NodeIndex u, NodeIndex v);

  auto nodeCount() const -> std::size_t;
  auto adjacentNodes(NodeIndex u) const -> const NodeList &;
};
