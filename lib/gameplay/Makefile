#
# Makefile pour la bibliotheque gameplay
#

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
CIBLE = libgameplay.a
CFLAGS += -std=c99 -D_DEFAULT_SOURCE -I ../utils

#
# Nom de la cible principale
#

all: $(CIBLE)

#
# Cible de nettoyage
#

clean: 
	rm -f core *.o $(CIBLE)

#
# Dependances pour la bibliotheque
#

$(CIBLE): $(OBJETS)
	$(AR) rs $@ $?

$(CIBLE:.a=).o: $(CIBLE:.a=).c $(CIBLE:.a=).h

#
# Formatage
#

format :
	clang-format -i -style=WebKit *.c *.h