#ifndef _BRESEN_H_
#define _BRESEN_H_

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include "Image.h"

//fonctions auxiliaires de Bresenham
void Z2_to_octant1(int xA, int yA, int xB, int yB, int *xA_1o, int *yA_1o, int *xB_1o, int *yB_1o);
void octant1_to_Z2(int xA, int yA, int xB, int yB, int x_1o, int y_1o, int *x, int *y);

//trace une droite de Bresenham
void I_bresenham(Image *img, int xA, int yA, int xB, int yB);
void I_bresenham_blue(Image *img, int xA, int yA, int xB, int yB);

//trace une droite horizontale
void I_droite_horizontale_sl(Image * img, int xA, int xB, int y);
void I_droite_horizontale(Image * img, int xA, int xB, int y);

//trace une droite verticale
void I_droite_verticale(Image * img, int x, int yA, int yB);

#endif
