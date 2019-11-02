#include "WeightedGraph.hpp"

void WeightedGraph::addEdge(NodeIndex u, NodeIndex v) { addEdge(u, v, 1.0); }

void WeightedGraph::addEdge(NodeIndex u, NodeIndex v, EdgeWeight w) {
  Graph::addEdge(u, v);
  setWeight(u, v, w);
}

auto WeightedGraph::weight(NodeIndex u, NodeIndex v) const -> EdgeWeight {
  return weights.find(std::make_tuple(u, v))->second;
}

void WeightedGraph::setWeight(NodeIndex u, NodeIndex v, EdgeWeight w) {
  weights[std::make_tuple(u, v)] = w;
}
