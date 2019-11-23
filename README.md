# Projet-FAIN
Projet réalisé dans le cadre de l'UE de *"Fondements et Algorithmes de
l'Imagerie Numérique"* : Saisie et remplissage d’un polygone 2D

# Installation des dépendances
Il faut installé la bibliothèque suivante : `sudo apt-get install freeglut3-dev`

# Pour utiliser le programme

Pour compiler le programme : `make`

Pour travailler sur une image 800 x 600 vierge (noire) : `./plot 800 600`

# Commandes disponibles
## Modes
### Mode insertion
Ce mode permet d'inserer des points à la fin du polygone. Il s'utilise de
la façon suivante :

* Pour activer ce mode il faut presser la touche `i`.
* Pour inserer un point, il suffit ensuite d'effectuer un clique gauche à la
souris dans la fenêtre.

### Mode vertex
Ce mode permet de travailler avec les vertex, autrement dit les points du
polygone. Il s'utilise de la façon suivante :

* Pour activer ce mode il faut presser la touche `v`.
* Pour passer au point suivant (respectivement précédent), il suffit d'appuyer
sur la touche `page suivante` :arrow_double_down: (respectivement `page précédente`:arrow_double_up:).
* Pour sélectionner un point, on peut également simplement faire un clique
gauche à la souris à proximité du point voulu.
* Pour supprimer un point il suffit de presser la touche `suppr`:wastebasket:
et le point sélectionné sera supprimé.
* Pour déplacer un point il faut presser une des quatre touche suivante :
  * :arrow_up: `haut` pour déplacer le point vers le haut ;
  * :arrow_down: `bas` pour déplacer le point vers le bas ;
  * :arrow_left: `gauche` pour déplacer le point vers la gauche ;
  * :arrow_right: `droite` pour déplacer le point vers la droite.

### Mode edge
Ce mode permet de travailler avec les edges, autrement dit les segements du polygone. Il s'utilise de la façon suivante :

* Pour activer ce mode il suffit de presser la touche `e`.
* Pour passer au segement suivant (respectivement précédent), il suffit d'appuyer
sur la touche `page suivante` :arrow_double_down: (respectivement `page précédente`:arrow_double_up:).
* Pour sélectionner un segement, on peut également simplement faire un clique
gauche à la souris à proximité du segement voulu.
* Pour ajouter un nouveau point au mileu du segement et ainsi creer un nouveau segement il suffit de presser la touche `m` ou d'utiliser le clique du mileu de la souris.

## Autres commandes

### Fermer un polygone
Pour fermer un polygone, il suffit de presser la touche `c`. Pour ouvrir un polygone fermé il suffit d'à nouveau presser la touche `c`.

### Remplir le polygone
Pour remplir un polygone, il est nécaissaire qu'il soit préalablement fermé,  ensuite il est possible de former un polygone plein en pressant la touche `f`.

# Exemple d'utilisation

L'encart du haut permet de voir quel commandes est utilisé pour effectuer l'action observée.

Le programme a tout d'abord été lancé avec la commande suivante : `./plot 400 400`

![GIF exemple projet FAIN](/Exemples/exemple_commandes.gif)

Il est également possible d'obtenir des images plus complexes comme celle-ci :

![IMAGE exemple projet FAIN](/Exemples/exemple_coq.png)

Cette image a été obtenue de la façon suivante :
* en premier on lance le programme à l'aide de la commande `./plot 400 400`
* ensuite en mode insertion on trace les différents points/droites nécessaire pour former l'image sauf la dernière droite
* cette dernière droite est formé à l'aide de la commande `c` qui permet de fermer le polygone
* on peut ensuite utilisé la commande `f` pour remplir le polygone
