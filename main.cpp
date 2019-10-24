#include <iostream>
#include <iterator>

#include "FindRoots.hpp"
#include "Graph.hpp"
#include "TopologicalSort.hpp"

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

int main() {
  test1();
  test2();

  return 0;
}
