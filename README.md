# Projet XMaze - Tutorat Système & Réseau SE2A4

## Sujet du projet

https://rex.plil.fr/Enseignement/Systeme/Tutorat.IMA2a4.XMaze/

## Auteur du sujet

### Xavier Redon

https://rex.plil.fr/

## Contenu du projet

Le projet permet de compiler deux exécutables représentant un serveur de jeu et un client pouvant être dupliqué pour jouer.

## Compilation du projet

Un fichier Makefile est situé à la racine et permet de compiler tous les répertoires du projet.

## Fonctionnement

### Connectivité

Le serveur et les clients communiquent leurs informations via des liaisons TCP et UDP :

* Le serveur diffuse des trames UDP avec les informations du serveur tant que le jeu n'est pas lancé pour que les clients le trouve et s'y connectent ensuite.
* Les clients effectuent des demandes de connexion TCP après avoir identifié un serveur de jeu. Cette connexion TCP permettra ensuite d'échanger des messages et des commandes dans un chat.
* Les clients envoient les touches pressées au serveur par liaison UDP.
* Le serveur calcule la projection 2D des scènes 3D de chaque client et les envoie aux clients pour un affichage.

### Descriptif des liaisons de communication

* Liaison UDP de diffusion des informations du serveur de jeu :
    - ip : 4 octets binaires non signés. IP du serveur de jeu.
    - id : 2 octets binaires non signés. ID du serveur de jeu.
    - port : 2 octets binaires non signés. Port de connexion TCP.
* Liaison TCP pour le chat et la connexion :
    - type : 1 octet binaire.
    - contenu : n octets dépendant du type du message.
        * Demande de connexion : type = 0x00
            - ip : 4 octets binaires non signés.
            - port : 2 octets binaires non signés. Il s'agit du port 
            - pseudo : 16 octets max. au format ASCII.
        * Connexion acceptée : type = 0x01
            - port : 2 octets binaires non signés. Port UDP de réception des touches.
            - id : 1 octet binaire non signé. ID du client.
        * Envoi d'un message sur le chat : type = 0x02
            - taille : 1 octet binaire non signé. Message de 255 caractères maximum.
            - message : tableau de n octets au format ASCII (n < 255). Une commande commence par le caractère '/'.
* Liaison UDP d'envoi des touches :
    - id : 1 octet binaire non signé. ID du client envoyant les touches.
    - touches : 1 octet binaire non signé.
        * bit 7 : Aller à droite
        * bit 6 : Aller à gauche
        * bit 5 : Reculer
        * bit 4 : Avancer
        * bit 3 : Tirer
* Liaison UDP d'envoi des scènes :
    - nb : 2 octets binaires non signés. Nombre total d'objets à envoyer.
    - id : 2 octets binaires non signés. Identifiant de l'objet courant.
    - objet : Structure de l'objet envoyé (type, position...).

