#include <iostream>
#include <iterator>

#include "Graph.hpp"
#include "TopologicalSort.hpp"

int main() {
  Graph g(6);
  g.addEdge(5, 2);
  g.addEdge(5, 0);
  g.addEdge(4, 0);
  g.addEdge(4, 1);
  g.addEdge(2, 3);
  g.addEdge(3, 1);

  std::cout << "Following is a Topological Sort of\n";
  auto top_order = topologicalSort(g);

  std::copy(begin(top_order), end(top_order),
            std::ostream_iterator<NodeIndex>{std::cout, " "});
  std::cout << '\n';

  return 0;
}
