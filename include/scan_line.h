#ifndef _SCAN_H_
#define _SCAN_H_

#include "polygone.h"

//calcul la boîte englobante d'un polygone
int getXmin(poly *polygone);
int getYmin(poly *polygone);
int getXmax(poly *polygone);
int getYmax(poly *polygone);

//teste l'intersection entre 2 segments et stocke ses coordonnées si elle existe
int line_intersection(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy, int *Ix, int *Iy);

//insertion d'un point en respectant un ordre croissant en x
void insert_point_order(poly *polygone, int x, int y);

//dessine le remplissage du polygone
void I_polygone_scan_line(Image *img, poly *polygone);

//remplissage d'un polygone
void scan_line(Image *img, poly *polygone);


#endif
