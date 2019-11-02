#include "Buildstats.hpp"

#include <fstream>
#include <regex>

namespace {
auto getPackageDirectories(const std::filesystem::path &root)
    -> std::unordered_map<std::string, std::string> {
  std::unordered_map<std::string, std::string> packageDirectories;

  const std::regex packageVersionRegex("(.*)-[0-9].*");
  std::smatch match;
  for (const auto &entry : std::filesystem::directory_iterator(root)) {
    if (!entry.is_directory()) {
      continue;
    }
    const auto packageDir = entry.path().filename().string();

    std::regex_match(packageDir, match, packageVersionRegex);
    const auto &packageName = match[1].str();
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

Buildstats::Buildstats(std::filesystem::path root)
    : root{root}, packageDirectories(getPackageDirectories(root)) {}

auto Buildstats::getElapsedTime(std::string_view nodeLabel) const -> double {

  auto pos = nodeLabel.find(".");
  auto packageName = nodeLabel.substr(0, pos);
  auto packageStage = nodeLabel.substr(pos + 1);

  const auto &packageDirectory =
      packageDirectories.find(std::string(packageName))->second;

  auto filePath = root / packageDirectory / packageStage;
  std::ifstream input(filePath);
  return parseElapsedTime(input);
}
