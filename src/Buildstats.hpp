#pragma once

#include <unordered_map>

#include <filesystem>
#include <optional>
#include <string>

using NodeLabel = std::string;

class Buildstats {
  std::filesystem::path root;
  std::unordered_map<NodeLabel, std::string> packageDirectories;

public:
  Buildstats(std::filesystem::path root);

  auto getElapsedTime(std::string_view nodeLabel) const
      -> std::optional<double>;
  auto getElapsedTimeOrDefault(std::string_view nodeLabel,
                               double defaultValue) const -> double;
};

auto directoryToPackageName(const std::string &packageDir) -> std::string;
