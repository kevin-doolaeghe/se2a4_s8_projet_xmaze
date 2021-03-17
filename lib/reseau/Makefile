#
# Makefile pour la bibliotheque reseau
#

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
CIBLE = libreseau.a
CFLAGS += -std=c99 -D_DEFAULT_SOURCE -I ../flux -I ../gameplay -I ../utils

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
