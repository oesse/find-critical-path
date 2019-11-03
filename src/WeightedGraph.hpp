#pragma once

#include <unordered_map>

#include "Graph.hpp"

using EdgeWeight = double;
using EdgeIndex = std::tuple<NodeIndex, NodeIndex>;
struct EdgeIndexHash {
  auto operator()(const EdgeIndex &idx) const noexcept -> std::size_t {
    std::size_t h1 = std::hash<NodeIndex>{}(std::get<0>(idx));
    std::size_t h2 = std::hash<NodeIndex>{}(std::get<1>(idx));
    return h1 ^ (h2 << 1);
  }
};

class WeightedGraph : public Graph {
  std::unordered_map<EdgeIndex, EdgeWeight, EdgeIndexHash> weights;

public:
  void addEdge(NodeIndex u, NodeIndex v);
  void addEdge(NodeIndex u, NodeIndex v, EdgeWeight w);
  auto weight(NodeIndex u, NodeIndex v) const -> EdgeWeight;
  void setWeight(NodeIndex u, NodeIndex v, EdgeWeight w);
};
