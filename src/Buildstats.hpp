#pragma once

#include <unordered_map>

#include <filesystem>
#include <string>

using NodeLabel = std::string;

class Buildstats {
  std::filesystem::path root;
  std::unordered_map<NodeLabel, std::string> packageDirectories;

public:
  Buildstats(std::filesystem::path root);

  auto getElapsedTime(std::string_view nodeLabel) const -> double;
};

auto directoryToPackageName(std::string packageDir) -> std::string;
