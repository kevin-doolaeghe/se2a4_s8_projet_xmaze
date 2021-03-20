#
# Makefile pour l'application client
#

SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
BIBLIOTHEQUES = -lm -lpthread -lSDL2_gfx -lSDL2
BIBLIOTHEQUES += -L ../../lib/flux -lflux
BIBLIOTHEQUES += -L ../../lib/gameplay -lgameplay
BIBLIOTHEQUES += -L ../../lib/graphique -lgraphique
BIBLIOTHEQUES += -L ../../lib/reseau -lreseau
BIBLIOTHEQUES += -L ../../lib/utils -lutils
CFLAGS += -std=c99 -D_DEFAULT_SOURCE
CFLAGS += -I ../../lib/flux
CFLAGS += -I ../../lib/gameplay
CFLAGS += -I ../../lib/graphique
CFLAGS += -I ../../lib/reseau
CFLAGS += -I ../../lib/utils
CIBLE = client

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
# Dependances pour l'executable
#

$(CIBLE): $(OBJETS)
	$(CC) -o $@ $^ $(BIBLIOTHEQUES)

#
# Formatage
#

format :
	clang-format -i -style=WebKit *.c *.h