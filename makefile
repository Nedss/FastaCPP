CXX=g++
CXX_FLAGS= -Wall -ansi -pedantic -std=c++11 -g -O0
LD_FLAGS=
EXTRA_FILES=Makefile README.md
PROG=fprog

all: .deps
	make $(PROG)

ifeq ($(wildcard .deps),.deps)
include .deps
endif

SOURCES=fasta.cpp main.cpp
HEADERS=fasta.h
.SUFFIXES: .h .cpp .o

.deps: $(SOURCES) $(HEADERS)
	$(CXX) -MM $^ > $@

.cpp.o:
	$(CXX) $(CXX_FLAGS) $< -c

$(PROG): $(SOURCES:.cpp=.o)
	$(CXX)  $(LD_FLAGS) $^ -o $@

clean:
	rm -f $(SOURCES:.cpp=.o)
	rm -f *~
	rm -f *$(PROG)
	rm -f .deps

save: $(SOURCES) $(HEADERS) $(EXTRA_FILES)
	tar -czf $(PROG)_$(shell date +"%F_%H-%M-%S_%Z").tar.gz $^
