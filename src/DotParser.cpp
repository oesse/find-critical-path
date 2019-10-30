#include "DotParser.hpp"

#include <boost/spirit/home/support/iterators/istream_iterator.hpp>
#include <boost/spirit/home/x3.hpp>

#include <iterator>

namespace dot {
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

template <typename Iterator>
auto parse_numbers(Iterator first, Iterator last) -> bool {
  using ascii::space;
  using x3::alnum;
  using x3::alpha;
  using x3::char_;
  using x3::lexeme;
  using x3::lit;
  using x3::phrase_parse;

  const auto quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];
  const auto word_string = alpha >> *(alnum | char_("_"));
  const auto id = (word_string | quoted_string);

  const auto graph_header = lit("digraph") >> id;

  const auto attr_list = lit("[") >> id >> lit("=") >> id >> lit("]");
  const auto node_stmt = id >> attr_list;

  const auto edge_stmt = id >> lit("->") >> id;

  const auto graph =
      graph_header >> lit("{") >> *(node_stmt | edge_stmt) >> lit("}");
  bool r = phrase_parse(first, last, graph, space);

  if (first != last) {
    return false;
  }
  return r;
}
} // namespace dot

DotParser::DotParser(std::istream &in) : in{in} { in.unsetf(std::ios::skipws); }
void DotParser::parse() {
  if (!dot::parse_numbers(boost::spirit::istream_iterator{in},
                          boost::spirit::istream_iterator{})) {
    throw std::runtime_error("parse error");
  }
}
