#include <filesystem>
#include <iostream>

#include "Buildstats.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <directory>\n";
    return -1;
  }

  const std::filesystem::path root{argv[1]};
  Buildstats stats{root};

  std::cout << stats.getElapsedTime("zip.do_compile") << '\n';

  return 0;
}
