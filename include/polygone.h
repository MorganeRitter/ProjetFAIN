#ifndef _POLY_H_
#define _POLY_H_

#include <stdbool.h>
#include <math.h>

#include "bresenham.h"

//structure representant un point
typedef struct struct_point {
	int x, y;
} point;

//structure representant un element de la liste chainee
typedef struct struct_element {
	point p; //structure point avec deux coordonne x et y
	struct struct_element *next; //pointeur vers l'element suivant
} ele;

//structure representant un polygone
typedef struct struct_polygone {
		size_t nb; //nb de points du polygone
		ele *first; //pointeur vers le premier element du polygone
		ele *last; //pointeur vers le dernier element du polygone
} poly;

//allocation d'un polygone
poly* create_polygone();

//desallocation d'un polygone
void delete_polygone(poly * polygone);

//tracé du polygone
void I_polygone(Image *img, poly *polygone);

//insertion d'un point à la fin du polygone
void insert_point(poly *polygone, int x, int y);

//insertion d'un point a la position indique
void insert_point_position(poly *polygone, int x, int y, int position);

/*----------------------------------------------*/

void polygone_select(Image *img, poly * polygone, int position);

void polygone_delete_point_first(poly * polygone);
void polygone_delete_point(poly * polygone, int position);

void polygone_move(poly *polygone, int position, int direction);

/*----------------------------------------------*/

void polygone_select_edge(Image *img, poly *polygone, int position);

void polygone_add_point_edge(poly *polygone, int position);

/*----------------------------------------------*/

int closestEdge(poly *polygone, int x, int y, bool closed);
int closestVertex(poly *polygone, int x, int y);

/*----------------------------------------------*/

//affiche les coordonnes des points du polygone
void display_polygone(poly *polygone);

#endif
