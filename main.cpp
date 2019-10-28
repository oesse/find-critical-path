#include <iostream>
#include <iterator>

#include "FindCriticalPath.hpp"
#include "FindRoots.hpp"
#include "Graph.hpp"
#include "TopologicalSort.hpp"
#include "WeightedGraph.hpp"

auto operator<<(std::ostream &out, const NodeList &nodes) -> std::ostream & {
  std::copy(begin(nodes), end(nodes),
            std::ostream_iterator<NodeIndex>{out, " "});
  return out;
}

void test1() {
  Graph g;
  g.addEdge(5, 2);
  g.addEdge(5, 0);
  g.addEdge(4, 0);
  g.addEdge(4, 1);
  g.addEdge(2, 3);
  g.addEdge(3, 1);

  auto topOrder = topologicalSort(g);
  auto roots = findRoots(g, topOrder);
  std::cout << "top: " << topOrder << '\n';
  std::cout << "roots: " << roots << '\n';
}

void test2() {
  Graph g;
  g.addEdge(5, 11);
  g.addEdge(7, 11);
  g.addEdge(7, 8);
  g.addEdge(3, 8);
  g.addEdge(3, 10);
  g.addEdge(11, 2);
  g.addEdge(11, 9);
  g.addEdge(11, 10);
  g.addEdge(8, 9);

  auto topOrder = topologicalSort(g);
  auto roots = findRoots(g, topOrder);

  std::cout << "top: " << topOrder << '\n';
  std::cout << "roots: " << roots << '\n';
}
void test3() {
  WeightedGraph g;
  g.addEdge(0, 1, 5);
  g.addEdge(0, 2, 3);
  g.addEdge(1, 3, 6);
  g.addEdge(1, 2, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 3, 7);
  g.addEdge(3, 5, 1);
  g.addEdge(3, 4, -1);
  g.addEdge(4, 5, -2);

  auto criticalPath = findCriticalPath(g, 5);
  std::cout << "critical path: " << criticalPath << '\n';
}

int main() {
  test3();
  return 0;
}
