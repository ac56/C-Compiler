CXX=clang++
CPPFLAGS=--std=c++14
LEXOPTS=
YACCOPTS=-W'all' -W'error'
# # For debugging bison
# YACCOPTS=$(YACCOPTS) --verbose --report-file='bison.output'
CXXFLAGS=-g
LINKFLAGS=-g

.PHONY: clean run testbench
.DEFAULT_GOAL := all
.PRECIOUS: src/parser.tab.hpp

headers=$(wildcard src/*.hpp)
sources=$(wildcard src/*.cpp)
objects=$(sort $(sources:.cpp=.o) src/parser.tab.o src/lexer.yy.o)

all: bin/c_compiler

bin/:
	@mkdir bin

src/c_parser.o: src/c_parser.cpp src/parser.tab.hpp

src/parser.tab.cpp src/parser.tab.hpp: src/parser.yy
	bison $(YACCOPTS) --defines=src/parser.tab.hpp --output=src/parser.tab.cpp $<

%.yy.cpp: %.ll src/parser.tab.hpp
	flex $(LEXOPTS) -o $@ $^

bin/c_compiler: bin/ $(objects) $(headers)
	$(CXX) $(LINKFLAGS) -o $@ $(objects)

clean:
	rm -rf bin src/parser.output $(objects) $(wildcard src/*.yy.cpp)
	rm -rf $(wildcard src/*.tab.*) $(wildcard test/*-results)

# Testing

.PHONY: test-translator

test-translator:
	./test-translator.sh | column -s, -t
