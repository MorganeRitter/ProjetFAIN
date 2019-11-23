#include "../include/scan_line.h"

/**
* getXmin : cherche la coordonne x minimale d'un polygone
*/
int getXmin(poly *polygone) {
	int min;

	if(polygone != NULL) {
		if(polygone->first != NULL) {
			min = polygone->first->p.x;
			ele *current_ele = polygone->first;

			//on parcours les segments du polygone
			while(current_ele->next != NULL) {
				if(current_ele->p.x < min) {
					min = current_ele->p.x;
				}
				current_ele = current_ele->next;
			}

			//on compare avec le dernier point
			if(polygone->last->p.x < min) {
				min = polygone->last->p.x;
			}
		}
	}

	return min;
}


/**
* getYmin : cherche la coordonne y minimale d'un polygone
*/
int getYmin(poly *polygone) {
	int min;

	if(polygone != NULL) {
		if(polygone->first != NULL) {
			min = polygone->first->p.y;
			ele *current_ele = polygone->first;

			while(current_ele->next != NULL) {
				if(current_ele->p.y < min) {
					min = current_ele->p.y;
				}
				current_ele = current_ele->next;
			}

			if(polygone->last->p.y < min) {
				min = polygone->last->p.y;
			}
		}
	}

	return min;
}


/**
* getXmax : cherche la coordonne x maximale d'un polygone
*/
int getXmax(poly *polygone) {
	int max;

	if(polygone != NULL) {
		if(polygone->first != NULL) {
			max = polygone->first->p.x;
			ele *current_ele = polygone->first;

			while(current_ele->next != NULL) {
				if(current_ele->p.x > max) {
					max = current_ele->p.x;
				}
				current_ele = current_ele->next;
			}

			if(polygone->last->p.x > max) {
				max = polygone->last->p.x;
			}
		}
	}

	return max;
}


/**
* getYmax : cherche la coordonne y maximale d'un polygone
*/
int getYmax(poly *polygone) {
	int max;

	if(polygone != NULL) {
		if(polygone->first != NULL) {
			max = polygone->first->p.y;
			ele *current_ele = polygone->first;

			while(current_ele->next != NULL) {
				if(current_ele->p.y > max) {
					max = current_ele->p.y;
				}
				current_ele = current_ele->next;
			}

			if(polygone->last->p.y > max) {
				max = polygone->last->p.y;
			}
		}
	}

	return max;
}

/**
 * line_intersection : teste si une intersection existe entre 2 droites
 * et stocke les coordonnées de cette intersection si elle existe
 * Params:
 * Ax - Ay : coordonnees du point A de la premiere droite
 * Bx - By : coordonnees du point B de la premiere droite
 * Cx - Cy : coordonnees du point C de la deuxieme droite
 * Dx - Dy : coordonnees du point D de la deuxieme droite
 * Ix - Iy : pointeurs vers les coordonnées de l'intersection
 */
int line_intersection(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy, int *Ix, int *Iy) {
	float ABx, ABy, DCx, DCy, CAx, CAy;
	float s, t, d;

	//coordonne x et y du vecteur AB
	ABx = (float)Bx - (float)Ax;
	ABy = (float)By - (float)Ay;

	//coordonne x et y du vecteur DC
	DCx = (float)Cx - (float)Dx;
	DCy = (float)Cy - (float)Dy;

	//coordonne x et y du vecteur CA
	CAx = (float)Ax - (float)Cx;
	CAy = (float)Ay - (float)Cy;

	//calcul du déterminant
	d = DCy*ABx - ABy*DCx;

	if(d != 0) {
		s = (DCx*CAy - CAx*DCy)/d;
		t = (CAx*ABy - ABx*CAy)/d;

		//on vérifie qu'il existe bien une intersection entre les 2 segments
		if ((s >= 0.0) && (s <= 1.0) && (t >= 0.0) && (t <= 1.0))
		{
			//on calcule les coordonnes de cette intersection
			if (Ix != NULL)
				*Ix = (int)(Ax + (s*ABx));
			if (Iy != NULL)
				*Iy = (int)(Ay + (s*ABy));
			return 1;
		}
	}

	return 0;
}


/**
	* insert_point_order : insertion d'un point en respectant l'ordre des x
	* dans une structure de type polygone
	* (utilise dans scan_line afin de trier les points d'intersection)
	* Params :
	* x : coordonnée x du nouveau point
	* y : coordonnée y du nouveau point
	*/
void insert_point_order(poly *polygone, int x, int y) {
	//creation du nouvel element
	ele *new_ele = malloc(sizeof(struct struct_element));
	if(new_ele == NULL) {
		exit(EXIT_FAILURE);
	}

	//création du point
	point new_point = {x, y};

	//initialisation du noeud
	new_ele->next = NULL;
	new_ele->p = new_point;

	if(polygone != NULL) {
		//si le polygone est vide
		if(polygone->nb == 0) {
			polygone->first = new_ele;
			polygone->last = new_ele;
		//si le polygone ne contient qu'un seul noeud
		} else if(polygone->nb == 1) {

			//si x est supérieur à la valeur existante
			if(x >= polygone->first->p.x) {
				//le nouvel element est inséré à la fin
				polygone->first->next = new_ele;
				polygone->last = new_ele;

			} else {
				//le nouvel element est inséré au début
				new_ele->next = polygone->first;
				polygone->first = new_ele;
			}

		//polygone de taille > 1
		} else {
			if(polygone->first != NULL) {
				ele *current_ele = polygone->first;
				//on parcours le polygone
				while(current_ele->next != NULL) {

					//on insert le nouvel element a la bonne position
					if((x >= current_ele->p.x) && (x <= current_ele->next->p.x)) {
						new_ele->next = current_ele->next;
						current_ele->next = new_ele;
						break;

					//on insert le nouvel element au début du polygone
					//seul cas où le x est inferieure au x du noeud courant
					} else if(x <= current_ele->p.x) {
						new_ele->next = polygone->first;
						polygone->first = new_ele;
						break;

					//on insert le nouvel element à la fin du polygone
					} else if(current_ele->next->next == NULL) {
						current_ele->next->next = new_ele;
						polygone->last = new_ele;
						break;

					//si le nouvel element n'est pas inséré
					//on continue le parcours
					} else
						current_ele = current_ele->next;
				}
			}
		}
	}
	polygone->nb++;
}


/**
 * I_polygone_scan_line : prends en parametre une structure polygone
 * et trace ce polygone
 * (utilise dans scan_line pour tracer le remplissage)
 * Params:
 * img : image ou dessiner le polygone
 * polygone : polygone a tracer
 */
void I_polygone_scan_line(Image *img, poly *polygone) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele *current_ele = polygone->first;

			//on parcourt les différents points et on
			//trace les droites entre les points
			while((current_ele != NULL) && (current_ele->next != NULL)) {
				I_droite_horizontale_sl(img,
					current_ele->p.x, current_ele->next->p.x,
					current_ele->next->p.y
				);
				current_ele = current_ele->next->next;
			}
		}
	}
}


/**
 * scan_line : remplissage d'un polygone à l'aide de l'algorithme scan line
 * Params:
 * img : image ou dessine le remplissage
 * polygone : polygone à remplir
 */
void scan_line(Image *img, poly *polygone) {
	int *inter_x = malloc(sizeof(int));
	int *inter_y = malloc(sizeof(int));

	//coordonnes de la boîte englobante
	int Xmin = getXmin(polygone);
	int Ymin = getYmin(polygone);
	int Xmax = getXmax(polygone);
	int Ymax = getYmax(polygone);

	//on prends un segment de la largeur de la boîte
	int xA = Xmin;
	int xB = Xmax;
	int y, intersection;

	//on parcours la boîte le long de l'axe y
	for(int i=Ymin; i<Ymax; i++) {

		//on stocke les intersections
		poly *liste_inter = create_polygone();

		//le segment descend le long de l'axe y (scan-line)
		y = i;

		*inter_x = -1;
		*inter_y = -1;

		if(polygone != NULL) {
			if(polygone->first != NULL) {
				ele *current_ele = polygone->first;

				//on parcours les segments du polygone
				while(current_ele->next != NULL) {

					//on test s'il y a intersection entre la ligne de scan
					//et le segment du polygone
					intersection = line_intersection(
						xA, y,
						xB, y,
						current_ele->p.x, current_ele->p.y,
						current_ele->next->p.x, current_ele->next->p.y,
						inter_x, inter_y
					);

					//on stocke l'intersection si elle existe
					if(intersection) {
						if(*inter_y != fmax(current_ele->p.y, current_ele->next->p.y))
							insert_point_order(liste_inter, *inter_x, *inter_y);
					}

					current_ele = current_ele->next;
				}

				//le segment entre le dernier point et le premier point
				//n'ai pas inclus dans le parcours du polygone
				intersection = line_intersection(
					xA, y,
					xB, y,
					polygone->last->p.x, polygone->last->p.y,
					polygone->first->p.x, polygone->first->p.y,
					inter_x, inter_y
				);

				if(intersection) {
					if(*inter_y != fmax(polygone->last->p.y, polygone->first->p.y))
						insert_point_order(liste_inter, *inter_x, *inter_y);
				}
			}
		}
		//parcours de la liste des intersections pour tracer
		//la ligne de remplissage en y
		I_polygone_scan_line(img, liste_inter);
		delete_polygone(liste_inter);
	}
	free(inter_x);
	free(inter_y);
}
