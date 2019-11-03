#include <fstream>
#include <iostream>
#include <iterator>

#include "Buildstats.hpp"
#include "FindCriticalPath.hpp"
#include "FindRoots.hpp"
#include "FindSinks.hpp"
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

  Buildstats stats{buildstatsPath};
  for (NodeIndex i = 0; i < g.graph().nodeCount(); ++i) {
    const auto label = g.getLabel(i).value();
    const auto elapsedTime = stats.getElapsedTimeOrDefault(label, 0.0);

    for (const auto adjacent : g.graph().adjacentNodes(i)) {
      g.graph().setWeight(i, adjacent, elapsedTime);
    }
  }

  return g;
}

auto main(int argc, const char *argv[]) -> int {
  if (argc != 3) {
    // NOLINTNEXTLINE cppcoreguidelines-pro-bounds-pointer-arithmetic
    std::cerr << "usage: " << argv[0]
              << " <path/to/task-depends.dot> <path/to/buildstats-dir>\n";
    return -1;
  }

  try {
    // NOLINTNEXTLINE cppcoreguidelines-pro-bounds-pointer-arithmetic
    const auto dotPath = argv[1];
    // NOLINTNEXTLINE cppcoreguidelines-pro-bounds-pointer-arithmetic
    const auto buildstatsPath = argv[2];
    auto g = loadGraph(dotPath, buildstatsPath);

    std::cout << "node count: " << g.graph().nodeCount() << '\n';

    auto sinks = findSinks(g.graph());
    auto virtualSinkId = g.graph().nodeCount();
    for (auto sinkId : sinks) {
      g.graph().addEdge(sinkId, virtualSinkId, 0.0);
    }
    auto criticalPath = findCriticalPath(g.graph(), virtualSinkId);

    auto toLabel = [&](NodeIndex i) { return g.getLabel(i).value(); };

    std::cout << "=============\n"
              << "critical path\n"
              << "=============\n";

    std::transform(begin(criticalPath), end(criticalPath) - 1,
                   std::ostream_iterator<std::string>{std::cout, "\n"},
                   toLabel);
    std::cout << '\n';
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return -1;
  }

  return 0;
}
