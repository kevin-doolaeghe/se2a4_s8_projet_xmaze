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

DIRS = flux gameplay graphique reseau utils

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
# Formatage
#

format: $(patsubst %, _format_%, $(DIRS))

$(patsubst %,_format_%,$(DIRS)):
	cd $(patsubst _format_%,%,$@) && $(MAKE) format