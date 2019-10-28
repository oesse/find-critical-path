#include "TopologicalSort.hpp"

#include <cassert>

#include <queue>

namespace {

auto countIncomingEdges(const Graph &g) -> std::vector<int> {
  const auto V = g.nodeCount();
  std::vector<int> in_degree(V, 0);

  // Traverse adjacency lists to fill indegrees of
  // vertices.  This step takes O(V+E) time
  for (int u = 0; u < V; u++) {
    for (auto adjacentIndex : g.adjacentNodes(u)) {
      in_degree[adjacentIndex]++;
    }
  }

  return in_degree;
}

void enqueueRootNodes(std::queue<NodeIndex> &q,
                      const std::vector<int> &in_degree) {
  for (int i = 0; i < in_degree.size(); i++) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }
}

} // namespace

auto topologicalSort(const Graph &g) -> NodeList {
  const auto V = g.nodeCount();

  std::vector<int> in_degree = countIncomingEdges(g);

  // Create an queue and enqueue all vertices with
  // indegree 0
  std::queue<NodeIndex> q;
  enqueueRootNodes(q, in_degree);

  // Initialize count of visited vertices
  std::size_t cnt = 0;

  NodeList top_order;

  // One by one dequeue vertices from queue and enqueue
  // adjacents if indegree of adjacent becomes 0
  while (!q.empty()) {
    // Extract front of queue (or perform dequeue)
    // and add it to topological order
    NodeIndex u = q.front();
    q.pop();
    top_order.push_back(u);

    // Iterate through all its neighbouring nodes
    // of dequeued node u and decrease their in-degree
    // by 1
    for (auto adjacentIndex : g.adjacentNodes(u)) {

      // If in-degree becomes zero, add it to queue
      if (--in_degree[adjacentIndex] == 0) {
        q.push(adjacentIndex);
      }
    }

    cnt++;
  }

  assert(cnt == V && "There must not be a cycle in the graph");

  return top_order;
}
