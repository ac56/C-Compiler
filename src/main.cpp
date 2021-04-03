#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <getopt.h>
#include "AST.hpp"
#include "c_parser.hpp"

using namespace std;

string usage(const string &program_name) {
  return "LOLnope c compiler\n"
         "\n"
         "  Usage:\n"
         "  " + program_name + " [--debug-parser] (-S|-t) <infile> [-o <outfile>]\n"
         "  " + program_name + " -h | --help\n"
         "\n"
         "  -h --help       Show this screen.\n"
         "  -S --assembly   Compile to assembly\n"
         "  -t --translate  Translate to python\n"
         "  -o <outfile>    The file to write the output to\n"
         "  --debug-parser  Show debugging information about the parser\n";
}

int main(int argc, char *argv[]) {
    bool more_args = true;
    bool debug_parser = false;
    enum OUTPUT_FORMAT { PYTHON, ASM, UNSET } output_format = UNSET;
    string infile_name("");

    ostream outstream(cout.rdbuf());
    ofstream outfile; // In case a file is specified

    /*** Parse args ***/
    const option long_options[] = {
        {"assembly",     required_argument, nullptr, 'S'},
        {"translate",    required_argument, nullptr, 't'},
        {"help",         no_argument,       nullptr, 'h'},
        {"debug-parser", no_argument,       nullptr, 'p'}
    };

    while (more_args) {
        int _indexptr; // ignored
        switch (getopt_long(argc, argv, "hS:t:o:", long_options, &_indexptr)) {
            case 'h':
                cerr << usage(argv[0]) << endl;
                exit(0);
                break;
            case 'S':
                output_format = ASM;
                infile_name = string(optarg);
                break;
            case 't':
                output_format = PYTHON;
                infile_name = string(optarg);
                break;
            case 'p':
                debug_parser = true;
                break;
            case 'o':
                outfile.open(optarg);
                outstream.rdbuf(outfile.rdbuf());
                break;
            case -1:
                more_args = false;
                break;
            case '?':
                cerr << usage(argv[0]) << endl;
                exit(1);
                break;

        }
    }

    /*** Errors ***/
    if (infile_name == "") {
        cerr << "No input file specified\n";
        cerr << usage(argv[0]) << endl;
        exit(1);
    }

    /*** Run ***/
    switch (output_format) {
        case ASM:
            try {
                parse(infile_name, debug_parser)
                    ->to_assembly(outstream);
            } catch (ParseError& err) {
                cerr << "Parse error\n";
                exit(2);
            }
            break;
        case PYTHON:
            try {
                parse(infile_name, debug_parser)
                    ->to_python("", outstream);
            } catch (ParseError& err) {
                cerr << "Parse error\n";
                exit(2);
            }
            break;
        case UNSET:
            cerr << "No output format specified\n";
            cerr << usage(argv[0]) << endl;
            exit(1);
            break;
    }
}
