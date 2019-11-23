#include "../include/bresenham.h"

/**
 * Z2_to_premier_octant : prends en parametre deux points quelconques
 * et les ramènes dans le premier octant
 * Params :
 * xA - yA : coordonnées du point A dans Z2
 * xB - yB : coordonnées du point B dans Z2
 * xA_1o - yA_1o : coordonnées du point A dans le premier octant
 * xB_1o - yB_1o : coordonnées du point B dans le premier octant
 */
void Z2_to_premier_octant(int xA, int yA, int xB, int yB, int *xA_1o, int *yA_1o, int *xB_1o, int *yB_1o) {
	int xA_1q, xB_1q, yA_1q, yB_1q;

	if(xB > xA) {
		xA_1q = xA;
		xB_1q = xB;
	//symétrie sur l'axe Oy
	} else {
		xA_1q = - xA;
		xB_1q = - xB;
	}

	if(yB > yA) {
		yA_1q = yA;
		yB_1q = yB;
	//symétrie sur l'axe Ox
	} else {
		yA_1q = - yA;
		yB_1q = - yB;
	}

	//on regarde si on est dans le premier octant (pente < 1)
	if((xB_1q - xA_1q) > (yB_1q - yA_1q)) {
		*xA_1o = xA_1q;
		*xB_1o = xB_1q;
		*yA_1o = yA_1q;
		*yB_1o = yB_1q;
	//sinon on est dans le 2e octant
	} else {
		*xA_1o = yA_1q;
		*xB_1o = yB_1q;
		*yA_1o = xA_1q;
		*yB_1o = xB_1q;
	}
}


/**
 * premier_octant_to_Z2 : prends en parametre un point P qui est
 * ramene dans l'octant des points A et B
 * Params:
 * xA - yA : coordonnées du point A
 * xB - yB : coordonnées du point B
 * xA_1o - yA_1o : coordonnées de P dans le premier octant
 * x - y : coordonnées du point P dans Z2
 */
void premier_octant_to_Z2(int xA, int yA, int xB, int yB, int x_1o, int y_1o, int *x, int *y) {
	int x_1q, y_1q;

	//on regarde si la pente de AB est inférieure à 1 (premier octant)
	if(abs(xB - xA) > abs(yB - yA)) {
		x_1q = x_1o;
		y_1q = y_1o;
	} else {
		x_1q = y_1o;
		y_1q = x_1o;
	}

	if(xB > xA) {
		*x = x_1q;
	//symétrie sur l'axe Oy
	} else {
		*x = -x_1q;
	}

	if(yB > yA) {
		*y = y_1q;
	//symétrie sur l'axe Ox
	} else {
		*y = -y_1q;
	}
}


/**
 * I_bresenham : dessine un segement de bresenham à partir
 * de deux points A et B
 * Params:
 * img : image ou la droite sera dessiner
 * xA - yA : coordonnées du point A du segement
 * xB - yB : coordonnées du point B du segement
 */
void I_bresenham(Image *img, int xA, int yA, int xB, int yB) {
	Color c = C_new(255, 255, 255);

	//coordonnes dans le premier octant
	int xA_1o, yA_1o, xB_1o, yB_1o;
	//coordonnees dans Z2
	int x_Z2, y_Z2;

	int dx, dy, incrd1, incrd2, x, y, d;

	//on ramene les points dans le premier octant
	Z2_to_premier_octant(xA, yA, xB, yB, &xA_1o, &yA_1o, &xB_1o, &yB_1o);

	//on utilise les nouvelles coordonnées de A et B pour faire les calculs
	dx = xB_1o - xA_1o;
	dy = yB_1o - yA_1o;
	incrd1 = 2*dy;
	incrd2 = 2*(dy-dx);

	x = xA_1o;
	y = yA_1o;
	d = 2*dy-dx;

	while(x <= xB_1o) {
		//avant d'afficher, on ramene le point obtenue dans le premier octant
		premier_octant_to_Z2(xA, yA, xB, yB, x, y, &x_Z2, &y_Z2);
		I_plotColor(img, x_Z2, y_Z2, c);

		x++;

		if(d<0)
			d += incrd1;
		else {
			y++;
			d += incrd2;
		}
	}
}


void I_bresenham_blue(Image *img, int xA, int yA, int xB, int yB) {
	Color c = C_new(0.0, 0.0, 1.0);

	//coordonnes dans le premier octant
	int xA_1o, yA_1o, xB_1o, yB_1o;
	//coordonnees dans Z2
	int x_Z2, y_Z2;

	int dx, dy, incrd1, incrd2, x, y, d;

	//on ramene les points dans le premier octant
	Z2_to_premier_octant(xA, yA, xB, yB, &xA_1o, &yA_1o, &xB_1o, &yB_1o);

	//on utilise les nouvelles coordonnées de A et B pour faire les calculs
	dx = xB_1o - xA_1o;
	dy = yB_1o - yA_1o;
	incrd1 = 2*dy;
	incrd2 = 2*(dy-dx);

	x = xA_1o;
	y = yA_1o;
	d = 2*dy-dx;

	while(x <= xB_1o) {
		//avant d'afficher, on ramene le point obtenue dans le premier octant
		premier_octant_to_Z2(xA, yA, xB, yB, x, y, &x_Z2, &y_Z2);
		I_plotColor(img, x_Z2, y_Z2, c);

		x++;

		if(d<0)
			d += incrd1;
		else {
			y++;
			d += incrd2;
		}
	}
}


/**
 * I_droite_horizontale : prends en parametre deux coordonnes x et
 * une coordonnes y puis trace une droite horizontale
 * Params :
 * img : image ou la droite horizontale est trace
 * xA - xB : coordonnes x
 * y : coordonnes y
 */
void I_droite_horizontale_sl(Image * img, int xA, int xB, int y) {
	Color c = C_new(1.0, 1.0, 1.0);
	int i = 0, max = 0;
	if(xA < xB) {
		i = xA;
		max = xB;
	} else {
		i = xB;
		max = xA;
	}
	for(i; i <= max; i++)
		I_plotColor(img, i, y, c);
}


void I_droite_horizontale(Image * img, int xA, int xB, int y) {
	 Color c = C_new(0.0, 1.0, 0.0);
	 int i = 0, max = 0;
	 if(xA < xB) {
		i = xA;
		max = xB;
	 }
	 else {
		i = xB;
		max = xA;
	 }
	for(i; i <= max; i++)
		I_plotColor(img, i, y, c);
}

void I_droite_verticale(Image * img, int x, int yA, int yB) {
	Color c = C_new(0.0, 1.0, 0.0);
	int i = 0, max = 0;
	if(yA < yB) {
		i = yA;
		max = yB;
	}
	else {
		i = yB;
		max = yA;
	}
 	for(i; i <= max; i++)
		I_plotColor(img, x, i, c);
}
