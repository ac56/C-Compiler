#include <cstdlib>
#include "c_parser.hpp"
#include "parser.tab.hpp"

using namespace std;

extern FILE* yyin;

unique_ptr<TranslationUnit> parse(std::string infile_name, bool debug_parser) {
    unique_ptr<TranslationUnit> result_ast(nullptr);
    yy::parser p(result_ast);

    p.set_debug_level(debug_parser);
    yyin = fopen(infile_name.c_str(), "r");

    if (p.parse() != 0) throw ParseError();

    return result_ast;
}
