#include <fstream>
#include <iostream>
#include <iterator>

#include "FindCriticalPath.hpp"
#include "FindRoots.hpp"
#include "Graph.hpp"
#include "LabeledGraph.hpp"
#include "ParseDotGraph.hpp"
#include "TopologicalSort.hpp"
#include "WeightedGraph.hpp"

auto loadGraph(const std::string &dotPath, const std::string &buildstatsPath)
    -> LabeledGraph<WeightedGraph> {
  LabeledGraph<WeightedGraph> g;

  auto onEdge = [&](const auto &srcLabel, const auto &destLabel) {
    g.addEdge(srcLabel, destLabel);
  };

  std::ifstream dotFile(dotPath);
  parseDotGraph(dotFile, onEdge);

  return g;
}

int main(int argc, const char *argv[]) {
  if (argc != 3) {
    std::cerr << "usage: " << argv[0]
              << " <path/to/task-depends.dot> <path/to/buildstats-dir>\n";
    return -1;
  }

  const auto dotPath = argv[1];
  const auto buildstatsPath = argv[2];
  const auto g = loadGraph(dotPath, buildstatsPath);

  std::cout << "node count: " << g.graph().nodeCount() << '\n';

  auto topOrder = topologicalSort(g.graph());
  auto roots = findRoots(g.graph(), topOrder);

  auto toLabel = [&](NodeIndex i) { return g.getLabel(i).value(); };

  std::cout << "=================\n"
            << "topological order\n"
            << "=================\n";

  std::transform(begin(topOrder), end(topOrder),
                 std::ostream_iterator<std::string>{std::cout, "\n"}, toLabel);
  std::cout << '\n';

  std::cout << "=====\n"
            << "roots\n"
            << "=====\n";

  std::transform(begin(roots), end(roots),
                 std::ostream_iterator<std::string>{std::cout, "\n"}, toLabel);
  std::cout << '\n';

  return 0;
}
