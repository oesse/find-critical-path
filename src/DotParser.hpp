#pragma once

#include <istream>

class DotParser {
  std::istream &in;

public:
  explicit DotParser(std::istream &in);
  void parse();
};
