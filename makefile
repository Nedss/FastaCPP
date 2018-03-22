################################################################################
#															Nicolas SOIRAT 																	 #
#																																							 #
#														Projet C++ Mapping																 #
#																																							 #
#												HMSN205 par Alban MANCHERON														 #
#																																							 #
#	Ceci est le makefile afin de compiler le programme C++. Il permet de réaliser#
#	quelques saves, de créer quelques archives et de faire quelques suppressions #
#																																							 #
################################################################################

														#############
														# Variables #
														#############

# COMPILATION
##############
CXX=g++
CXX_FLAGS= -Wall -ansi -pedantic -std=c++11 -g -O0

#FICHIERS
#########
PROGNAME=projetcpp
ARCH=$(PROGNAME).tar.gz
ARCH_SRC=$(PROGNAME)_src.tar.gz
SOURCES=fasta.cpp main.cpp
HEADERS=fasta.h
THIS=makefile
VERSION='eval\date\+%d_%m_%Y'

# SHELL
#######
CIBLE_ACTUELLE=@
RM=$(CIBLE_ACTUELLE)rm -f
LS=$(CIBLE_ACTUELLE)ls -a --color
MV=$(CIBLE_ACTUELLE)mv
MKDIR=$(CIBLE_ACTUELLE)mkdir -p
CLEAR=$(CIBLE_ACTUELLE)CLEAR
MAKE=$(CIBLE_ACTUELLE)makefile
TAR=$(CIBLE_ACTUELLE)tar -czf

################################################################################

																##########
																# CIBLES #
																##########

# USUELLES
##########
ifeq($(wildcard .deps), )
all : .deps
			$(MAKE)
else
all : $(PROGNAME)
endif
dep : .deps
arch : $(ARCH)
arch_src : $(ARCH_SRC)
save : $(VERSION)

# ARCHIVAGE
###########
$(ARCH) : $(THIS) $(PROGNAME) $(HEADERS) $(SOURCES:.cpp=.h) $(SOURCES:.cpp=.o)
			$(CIBLE_ACTUELLE) "Création de l'archive $@\n\tAjout des fichiers : $^"
			$(TAR) $@ $^
			##$(MSG_OK)
$(ARCH_SRC) : $(THIS) $(SOURCES) $(SOURCES:.cpp=.h) $(HEADERS)
			#$(MSG) "Création de l'archive $@\n\tAjout des fichiers : $^"
			$(TAR) $@ $^
			#$(MSG_OK)
$(VERSION) : $(ARCH_SRC)
			#$(MSG) "Creation du répertoire de sauvegarde : $@"
			$(RM) -rf $@
			$(MKDIR) $@
			#$(MSG) "Sauvegarde de l'archive $<"
			$(MV) $< $@
			#$(MSG_OK)

#NETTOYAGE
##########
cls:
			#$(MSG) "On fait le ménage"
			$(RM) \#*
			$(RM) $(RM) ∗˜
			$(RM) core
			$(RM) *.o
			$(RM) $(PROGNAME)
			$(RM) $(ARCH)
			$(RM) $(ARCH_SRC)
			#$(MSG_OK)
clean: cls
			$(CLEAR)
			$(LS)

#COMPILATION
#############
.SUFFIXES : .h .cpp .o
.deps : $(SOURCES)
			#$(MSG) "Recherche des dépendances des fichiers ..."
			$(RM) .deps
			$(CXX) -MM $^ >> $@
			#$(MSG_OK)
.c.o:
			#$(MSG1)
			$(CXX) -c $(CXX_FLAGS) $<
			#$(MSG_OK)
$(PROGNAME)  : $(SOURCES:.cpp=.o)
			$(CXX) $^ -o $@
