#
# Makefile pour le projet labyrinthe
#

#
# Constantes pour la compilation
#

CC = gcc
LD = gcc
AR = ar
export CFLAGS += -g -Wall
MAKE = make

#
# Constantes du projet
#

DIRS=Graphique Labyrinthe

#
# Cible principale
#

all: $(patsubst %, _dir_%, $(DIRS))

$(patsubst %,_dir_%,$(DIRS)):
	cd $(patsubst _dir_%,%,$@) && $(MAKE)

#
# Cible de deverminage
#

debug: CFLAGS += -DDEVERMINE
debug: all

#
# Cible de nettoyage
#

clean: $(patsubst %, _clean_%, $(DIRS))

$(patsubst %,_clean_%,$(DIRS)):
	cd $(patsubst _clean_%,%,$@) && $(MAKE) clean

#
# Installation SDL
#

prepare:
	apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-gfx-dev
