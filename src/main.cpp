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

auto connectVirtualSink(WeightedGraph &g) -> NodeIndex {
    auto sinks = findSinks(g);
    auto virtualSinkId = g.nodeCount();
    for (auto sinkId : sinks) {
      g.addEdge(sinkId, virtualSinkId, 0.0);
    }
    return virtualSinkId;
}

void printCriticalPath(std::ostream &out, const NodeList &criticalPath, const LabeledGraph<WeightedGraph> &g) {
    for (const auto nodeId : criticalPath) {
      const auto label = g.getLabel(nodeId);
      if (!label.has_value()) {
        break;
      }

      const auto &adjacentNodes = g.graph().adjacentNodes(nodeId);
      const auto elapsedTime =
          adjacentNodes.empty() ? 0.0 : g.graph().weight(nodeId, adjacentNodes.front());

      out << label.value() << " " << elapsedTime << '\n';
    }
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

    const auto virtualSinkId = connectVirtualSink(g.graph());
    const auto criticalPath = findCriticalPath(g.graph(), virtualSinkId);

    printCriticalPath(std::cout, criticalPath, g);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return -1;
  }

  return 0;
}
