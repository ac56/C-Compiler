#pragma once

#include "memory"
#include "AST.hpp"

/**
 * Raised on bison parse errors. Contains no information for now.
 */
class ParseError : public std::exception {
    public:
        const char* what() const noexcept override { return "Parsing failed"; }
};

/**
 * Parse the file infile_name
 * debug_parser enables bison's debugging output
 */
std::unique_ptr<TranslationUnit> parse(std::string infile_name, bool debug_parser=false);
