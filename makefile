################################################################################
#															Nicolas SOIRAT 																	 #
#																																							 #
#														Projet C++ Mapping																 #
#																																							 #
#												HMSN205 par Alban MANCHERON														 #
#																																							 #
#	Ceci est le makefile afin de compiler le programme C++. Il permet de réaliser#
#	quelques saves ainsi que de supprimer les fichiers link 										 #
#																																							 #
################################################################################

																#############
																# Variables #
																#############


# COMPILATION
##############
CXX=g++
CXX_FLAGS= -Wall -ansi -pedantic -std=c++11 -g -O0
#LD_FLAGS=
EXTRA_FILES=Makefile README.md
PROG=fprog


																##########
																# CIBLES #
																##########


#USUELLES
#########
all: .deps
	make $(PROG)
ifeq ($(wildcard .deps),.deps)
include .deps
endif

#COMPILATION
############
SOURCES=fasta.cpp EncodedSeq.cpp main.cpp
HEADERS=fasta.h EncodedSeq.cpp
.SUFFIXES: .h .cpp .o

.deps: $(SOURCES) $(HEADERS)
	$(CXX) -MM $^ > $@

.cpp.o:
	$(CXX) $(CXX_FLAGS) $< -c

$(PROG): $(SOURCES:.cpp=.o)
	$(CXX) $(LD_FLAGS) $^ -o $@

#NETTOYAGE
##########
clean:
	rm -f $(SOURCES:.cpp=.o)
	rm -f *~
	rm -f *$(PROG)
	rm -f .deps

#SAUVEGARDE
############
save: $(SOURCES) $(HEADERS) $(EXTRA_FILES)
	tar -czf $(PROG)_$(shell date +"%F_%H-%M-%S_%Z").tar.gz $^
