#pragma once

#include <unordered_map>

#include "Graph.hpp"

using NodeLabel = std::string;

template <typename GraphType> class LabeledGraph {
  GraphType g;
  std::unordered_map<NodeIndex, NodeLabel> nodeLabels;
  std::unordered_map<NodeLabel, NodeIndex> nodeIds;
  NodeIndex lastId = 0;

public:
  auto graph() -> GraphType &;
  auto graph() const -> const GraphType &;

  void addEdge(const NodeLabel &src, const NodeLabel &dest);

  auto getIndex(const NodeLabel &label) const -> std::optional<NodeIndex>;
  auto getLabel(NodeIndex id) const -> std::optional<NodeLabel>;

private:
  auto getOrCreateNodeId(const NodeLabel &label) -> NodeIndex;
};

template <typename GraphType>
auto LabeledGraph<GraphType>::graph() -> GraphType & {
  return g;
}
template <typename GraphType>
auto LabeledGraph<GraphType>::graph() const -> const GraphType & {
  return g;
}

template <typename GraphType>
void LabeledGraph<GraphType>::addEdge(const NodeLabel &src,
                                      const NodeLabel &dest) {
  const auto srcNodeId = getOrCreateNodeId(src);
  const auto destNodeId = getOrCreateNodeId(dest);
  g.addEdge(srcNodeId, destNodeId);
}

template <typename GraphType>
auto LabeledGraph<GraphType>::getLabel(NodeIndex id) const
    -> std::optional<NodeLabel> {
  auto it = nodeLabels.find(id);
  if (it != nodeLabels.end()) {
    return it->second;
  }
  return std::nullopt;
}

template <typename GraphType>
auto LabeledGraph<GraphType>::getIndex(const NodeLabel &label) const
    -> std::optional<NodeIndex> {
  auto it = nodeIds.find(label);
  if (it != end(nodeIds)) {
    return it->second;
  }
  return std::nullopt;
}

template <typename GraphType>
auto LabeledGraph<GraphType>::getOrCreateNodeId(const NodeLabel &label)
    -> NodeIndex {
  auto idx = getIndex(label);
  if (idx) {
    return idx.value();
  }

  nodeIds.insert({label, lastId});
  nodeLabels.insert({lastId, label});
  return lastId++;
}
