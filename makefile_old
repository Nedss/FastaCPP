CXX=g++
CXX_FLAGS= -Wall -ansi -pedantic -std=c++11 -g -O0
EXTRA_FILES=Makefile README.md
PROG=fprog

#ifeq ($(wildcard .deps), )
#all:.deps
#	make
#else
#all:$(PROG)
#include .deps
#endif


SOURCES=fasta.cpp main.cpp
HEADERS=fasta.h
.SUFFIXES: .h .cpp .o
#.deps:
#	$(SOURCES) $(HEADERS)
#	$(CXX) -MM $^ > $@
.cpp.o:
	$(CXX) $(CXX_FLAGS) $< -c
	$(PROG):$(SOURCES:.cpp=.o)
	$(CXX) $^ -o $@
#clean:
#	rm -f $(SOURCES:.cpp=.o)
#	rm -f *~
#	rm -f *$(PROG)
#	rm -f .deps
#save:
#	$(PROG).tar.gz
#	$(PROG).tar.gz:$(SOURCES) $(HEADERS) $(EXTRA_FILES)
#	mv $@ $@.tmp
#	tar -czf $@ $^
#	rm -f $@.tmp
