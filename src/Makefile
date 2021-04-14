#
# Makefile pour les exécutable du projet
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

DIRS = client serveur labyrinthe

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