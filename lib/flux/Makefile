#
# Makefile pour la bibliotheque flux
#

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
CIBLE = libflux.a
CFLAGS += -std=c99 -D_DEFAULT_SOURCE

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