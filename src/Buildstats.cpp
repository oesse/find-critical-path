#include "Buildstats.hpp"

#include <fstream>
#include <regex>

namespace {
auto getPackageDirectories(const std::filesystem::path &root)
    -> std::unordered_map<std::string, std::string> {
  std::unordered_map<std::string, std::string> packageDirectories;

  for (const auto &entry : std::filesystem::directory_iterator(root)) {
    if (!entry.is_directory()) {
      continue;
    }
    const auto packageDir = entry.path().filename().string();
    const auto packageName = directoryToPackageName(packageDir);
    packageDirectories.insert({packageName, packageDir});
  }

  return packageDirectories;
}

const std::regex elapsedTimeRegex("Elapsed time: ([0-9]+\\.[0-9]+) seconds");

auto parseElapsedTime(std::istream &input) -> double {
  for (std::string line; std::getline(input, line);) {
    std::smatch match;
    if (std::regex_match(line, match, elapsedTimeRegex)) {
      const auto &timeAsString = match[1].str();
      try {
        return std::stod(timeAsString);
      } catch (const std::exception &e) {
        throw std::runtime_error(
            "invalid file format. could not parse elapsed time");
      }
    }
  }

  throw std::runtime_error("invalid file format. could not find elapsed time");
}

} // namespace

const std::regex packageVersionRegex("(.*)-([0-9]|git).*");
auto directoryToPackageName(const std::string &packageDir) -> std::string {
  std::smatch match;
  std::regex_match(packageDir, match, packageVersionRegex);
  return match[1].str();
}

Buildstats::Buildstats(std::filesystem::path root)
    : root{std::move(root)},
      packageDirectories(getPackageDirectories(this->root)) {}

auto Buildstats::getElapsedTime(std::string_view nodeLabel) const
    -> std::optional<double> {
  auto pos = nodeLabel.rfind(".");
  auto packageName = nodeLabel.substr(0, pos);
  auto packageStage = nodeLabel.substr(pos + 1);

  auto it = packageDirectories.find(std::string(packageName));
  if (it == packageDirectories.end()) {
    return std::nullopt;
  }

  const auto &packageDirectory = it->second;

  auto filePath = root / packageDirectory / packageStage;
  std::filesystem::directory_entry entry{filePath};
  if (!entry.is_regular_file()) {
    return std::nullopt;
  }

  std::ifstream input(filePath);
  return parseElapsedTime(input);
}

auto Buildstats::getElapsedTimeOrDefault(std::string_view nodeLabel,
                                         double defaultValue) const -> double {
  const auto elapsed = getElapsedTime(nodeLabel);
  if (elapsed.has_value()) {
    return elapsed.value();
  }
  return defaultValue;
}
