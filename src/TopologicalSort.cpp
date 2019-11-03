#include "TopologicalSort.hpp"

#include <cassert>

#include <queue>

namespace {

auto countIncomingEdges(const Graph &g) -> std::vector<int> {
  const auto V = g.nodeCount();
  std::vector<int> inDegree(V, 0);

  // Traverse adjacency lists to fill indegrees of
  // vertices.  This step takes O(V+E) time
  for (NodeIndex u = 0; u < V; u++) {
    for (auto adjacentIndex : g.adjacentNodes(u)) {
      inDegree[adjacentIndex]++;
    }
  }

  return inDegree;
}

void enqueueRootNodes(std::queue<NodeIndex> &q,
                      const std::vector<int> &inDegree) {
  for (NodeIndex i = 0; i < inDegree.size(); i++) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }
}

} // namespace

auto topologicalSort(const Graph &g) -> NodeList {
  const auto V = g.nodeCount();

  std::vector<int> inDegree = countIncomingEdges(g);

  // Create an queue and enqueue all vertices with
  // indegree 0
  std::queue<NodeIndex> q;
  enqueueRootNodes(q, inDegree);

  // Initialize count of visited vertices
  std::size_t cnt = 0;

  NodeList topOrder;

  // One by one dequeue vertices from queue and enqueue
  // adjacents if indegree of adjacent becomes 0
  while (!q.empty()) {
    // Extract front of queue (or perform dequeue)
    // and add it to topological order
    NodeIndex u = q.front();
    q.pop();
    topOrder.push_back(u);

    // Iterate through all its neighbouring nodes
    // of dequeued node u and decrease their in-degree
    // by 1
    for (auto adjacentIndex : g.adjacentNodes(u)) {

      // If in-degree becomes zero, add it to queue
      if (--inDegree[adjacentIndex] == 0) {
        q.push(adjacentIndex);
      }
    }

    cnt++;
  }

  assert(cnt == V && "There must not be a cycle in the graph");

  return topOrder;
}
