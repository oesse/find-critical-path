#include "ParseDotGraph.hpp"

#include <boost/fusion/tuple.hpp>
#include <boost/spirit/home/support/iterators/istream_iterator.hpp>
#include <boost/spirit/home/x3.hpp>

#include <iterator>

namespace dot {

namespace x3 = boost::spirit::x3;
namespace fusion = boost::fusion;

using x3::alnum;
using x3::alpha;
using x3::char_;
using x3::lexeme;
using x3::lit;
using x3::rule;

const auto quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];
const auto word_string = alpha >> *(alnum | char_("_"));
const auto id = (word_string | quoted_string);

const rule<class edge, fusion::tuple<std::string, std::string>> edge_stmt =
    "edge";
const auto edge_stmt_def = id >> lit("->") >> id;

const auto attr_list = lit("[") >> id >> lit("=") >> id >> lit("]");
const auto node_stmt = id >> attr_list;

const auto graph_header = lit("digraph") >> id;

BOOST_SPIRIT_DEFINE(edge_stmt); // NOLINT

template <typename Iterator>
auto parse(Iterator first, Iterator last, const OnEdgeFunction &onEdge)
    -> bool {
  const auto on_edge = [&](auto &ctx) {
    const auto &attribute = x3::_attr(ctx);
    const auto &srcId = fusion::get<0>(attribute);
    const auto &destId = fusion::get<1>(attribute);
    onEdge(srcId, destId);
  };

  const auto graph =
      graph_header >> lit("{") >> *(node_stmt | edge_stmt[on_edge]) >> lit("}");
  bool r = x3::phrase_parse(first, last, graph, x3::ascii::space);

  if (first != last) {
    return false;
  }
  return r;
}
} // namespace dot

void parseDotGraph(std::istream &in, OnEdgeFunction onEdge) {
  in.unsetf(std::ios::skipws);
  if (!dot::parse(boost::spirit::istream_iterator{in},
                  boost::spirit::istream_iterator{}, onEdge)) {
    throw std::runtime_error("parse error");
  }
}
