#include "../include/polygone.h"

/**
 * create_polygone : alloue la memoire pour un polygone
 * et l'initialise
 */
poly* create_polygone() {
	poly* polygone = malloc(sizeof(struct struct_polygone));
	if(polygone == NULL) {
		exit(EXIT_FAILURE);
	}

	polygone->nb = 0;
	polygone->first = NULL;
	polygone->last = NULL;

	return polygone;
}


/**
* delete_polygone : desalloue la memoire pour un polygone
*/
void delete_polygone(poly * polygone) {
	if(polygone != NULL) {
		ele *ele_temp = polygone->first;
		while(ele_temp != NULL) {
			ele *ele_del = ele_temp;
			ele_temp = ele_temp->next;
			free(ele_del);
		}
		free(polygone);
	}
}

/**
 * I_polygone : prends en parametre une structure polygone
 * et trace ce polygone
 */
void I_polygone(Image *img, poly *polygone) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele *current_ele = polygone->first;

			//on parcourt les différents points et on
			//trace les droites entre les points
			while(current_ele->next != NULL) {
				I_bresenham(img,
					current_ele->p.x, current_ele->p.y,
					current_ele->next->p.x, current_ele->next->p.y
				);
				current_ele = current_ele->next;
			}
		}
	}
}


/**
 * insert_point : on insere un nouveau point à la fin de la
 * liste chainee polygone
 * Params :
 * x : coordonne x du nouveau point
 * y : coordonne y du nouveau point
 */
void insert_point(poly *polygone, int x, int y) {
	if(polygone != NULL) {
		ele *new_ele = malloc(sizeof(struct struct_element));
		if(new_ele == NULL) {
			exit(EXIT_FAILURE);
		}

		point new_point = {x, y};
		new_ele->p = new_point;

		//on initialise le pointeur vers l'element suivant
		new_ele->next = NULL;

		//on ajoute new_ele à la liste chainee
		//si polygone est vide on ajoute l'element
		//en tant que premier et dernier element de la liste
		if(polygone->nb == 0) {
			polygone->first = new_ele;
			polygone->last = new_ele;

		} else {
			//sinon on ajoute le nouvel element à la fin
			polygone->last->next = new_ele;
			polygone->last = new_ele;
		}
		polygone->nb++;
	}
}



/**
 * insert_point_position : insert un point dans la structure polygone à la
 * position indique en parametre
 * (utilise dans polygone_add_point_edge)
 */
void insert_point_position(poly *polygone, int x, int y, int position) {
	if(polygone != NULL) {
		//on insere le point au début du polygone
		if(position == 1 && polygone->first != NULL) {
			ele *new_ele = malloc(sizeof(struct struct_element));

			if(new_ele == NULL)
				exit(EXIT_FAILURE);

			point new_point = {x, y};
			new_ele->p = new_point;
			new_ele->next = polygone->first->next;
			polygone->first->next = new_ele;
			polygone->nb++;

		} else if(polygone->first != NULL) {
			ele * current_ele = polygone->first;
			int i = 1;

			//on parcours le polygone jusqu'a trouver le point apres le quel
			//on veut insere le nouveau point
			while((i != position) && (current_ele->next != NULL)) {
				i++;
				current_ele = current_ele->next;
			}

			if(position != polygone->nb) {
				ele *new_ele = malloc(sizeof(struct struct_element));

				if(new_ele == NULL)
					exit(EXIT_FAILURE);

				point new_point = {x, y};
				new_ele->p = new_point;

				new_ele->next = current_ele->next;
				current_ele->next = new_ele;
				polygone->nb++;
			} else
				//dernier point
				insert_point(polygone,x,y);
		}
	}
}


/**
 * polygone_select : selectionne un point, c'est-à-dire trace un carre vert
 * autour, a la position entrer en parametre
 */
void polygone_select(Image *img, poly * polygone, int position) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele * current_ele = polygone->first;
			int i = 1;

			//on parcourt le polygone jusqu'à trouver la bonne position
			while((current_ele != NULL) && (i <= position)) {
				if(i == position) {
					//tracer du carre
					I_droite_verticale(img, (current_ele->p.x)+5, (current_ele->p.y)-5, (current_ele->p.y)+5);
					I_droite_verticale(img, (current_ele->p.x)-5, (current_ele->p.y)-5, (current_ele->p.y)+5);
					I_droite_horizontale(img, (current_ele->p.x)-5, (current_ele->p.x)+5, (current_ele->p.y)+5);
					I_droite_horizontale(img, (current_ele->p.x)-5, (current_ele->p.x)+5, (current_ele->p.y)-5);
				} else
					current_ele = current_ele->next;
				i++;
			}
		}
	}
}


/**
 * polygone_delete_point_first : supprime le premier point du polygone
 */
void polygone_delete_point_first(poly * polygone) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele * current_ele = polygone->first;
			if(polygone->nb != 1)
				polygone->first = current_ele->next;
			else {
				polygone->first = NULL;
				polygone->last = NULL;
			}
			free(current_ele);
			polygone->nb--;
		}
	}
}


/**
 * polygone_delete_point : supprime le point indique par position
 */
void polygone_delete_point(poly * polygone, int position) {
	if(polygone != NULL) {
		if(position == 1) {
			polygone_delete_point_first(polygone);
		} else if(polygone->first != NULL) {
			ele * current_ele = polygone->first;
			int i = 1;
			//on parcours le polygone jusqu'a trouver le point précédent
			//a celui qu'on cherche à supprime
			while((i != position-1) && (current_ele->next != NULL)) {
				i++;
				current_ele = current_ele->next;
			}

			if(position != polygone->nb) {
				//on relie le point precedent au point suivant qu'on cherche
				//a supprime
				current_ele->next = current_ele->next->next;
			} else {
				//dernier point
				current_ele->next = NULL;
				polygone->last = current_ele;
			}
			polygone->nb--;
		}
	}
}


/**
 * polygone_move : deplace le point indique par position dans une direction
 * direction : 0 -> gauche		1 -> droite		2 -> haut		3 -> bas
 * (en prenant comme reference l'ecran)
 */
void polygone_move(poly *polygone, int position, int direction) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele * current_ele = polygone->first;
			int i = 1;
			while(current_ele != NULL && i <= position) {
				if(i == position) {
					switch (direction) {
						case 0 :
							current_ele->p.x-=1;
							break;
						case 1 :
							current_ele->p.x+=1;
							break;
						case 2 :
							current_ele->p.y-=1;
							break;
						case 3 :
							current_ele->p.y+=1;
							break;
						default :
							break;
					}
				} else
					current_ele = current_ele->next;
				i++;
			}
		}
	}
}


/**
 * polygone_select_edge : selectionne un segement du polygone, c'est-a-dire
 * le dessine en bleu, indique par position
 */
void polygone_select_edge(Image *img, poly *polygone, int position) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele * current_ele = polygone->first;
			int i = 1;
			while(current_ele != NULL && i < position) {
				current_ele = current_ele->next;
				i++;
			}
			//si c'est le dernier segement qu'on cherche a selectionne
			if(current_ele->next == NULL) {
					I_bresenham_blue( img,
					polygone->last->p.x,  polygone->last->p.y,
					polygone->first->p.x, polygone->first->p.y);
			} else {
				I_bresenham_blue( img,
					current_ele->p.x, current_ele->p.y,
					current_ele->next->p.x, current_ele->next->p.y);
			}
		}
	}
}


/**
 * polygone_add_point_edge : ajoute un nouveau point entre les deux extremite
 * du segement selectionne indique par position
 */
void polygone_add_point_edge(poly *polygone, int position) {
	if(polygone != NULL) {
		if(polygone->first != NULL) {

			int x_new, y_new;
			ele * current_ele = polygone->first;
			int i = 1;

			while(current_ele != NULL && i < position) {
				current_ele = current_ele->next;
				i++;
			}

			//si on cherche a subdiviser le dernier segment
			if(current_ele->next == NULL) {
					//calcul des coordonnes du nouveau point
					x_new = (polygone->last->p.x + polygone->first->p.x)/2;
					y_new = (polygone->last->p.y + polygone->first->p.y)/2;
					insert_point_position(polygone, x_new, y_new, position);
			} else {
					x_new = (current_ele->p.x + current_ele->next->p.x)/2;
					y_new = (current_ele->p.y + current_ele->next->p.y)/2;
					insert_point_position(polygone, x_new, y_new, position);
			}
		}
	}
}

/**
 * closestEdge : trouve le segment le plus proche des coordonnes x et y
 * Params :
 * x : coordonne x dont on cherche le segment le plus proche
 * y : coordonne y dont on cherche le segment le plus proche
 * closed : permet de savoir si le dernier segement doit etre
 * pris en compte ou non
 */
int closestEdge(poly *polygone, int x, int y, bool closed) {
	int min, indice = 0, distance, x_s, y_s;
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele * current_ele = polygone->first;

			x_s = (current_ele->p.x + current_ele->next->p.x)/2;
			y_s = (current_ele->p.y + current_ele->next->p.y)/2;

			distance = sqrt(pow(x - x_s,2) + pow(y - y_s, 2));

			min = distance;
			indice = 1;
			int i = 2;

			current_ele = current_ele->next;

			while(current_ele->next != NULL) {
				x_s = (current_ele->p.x + current_ele->next->p.x)/2;
				y_s = (current_ele->p.y + current_ele->next->p.y)/2;

				distance = sqrt(pow(x - x_s,2) + pow(y - y_s, 2));

				if(distance < min) {
					min = distance;
					indice = i;
				}
				i++;
				current_ele = current_ele->next;
			}
			//si le polygone est ferme on regarde aussi si le dernier
			//segement est le plus proche ou non
			if(closed) {
				x_s = (polygone->first->p.x + polygone->last->p.x)/2;
				y_s = (polygone->first->p.y + polygone->last->p.y)/2;

				distance = sqrt(pow(x - x_s,2) + pow(y - y_s, 2));

				if(distance < min) {
					min = distance;
					indice = polygone->nb;
				}
			}
		}
	}
	return indice;
}

/**
 * closestVertex : cherche le point le plus proche des coordonnes x et y
 * Params :
 * x : coordonne x dont on cherche le point le plus proche
 * y : coordonne y dont on cherche le point le plus proche
 */
int closestVertex(poly *polygone, int x, int y) {
	int min, indice = 0, distance;
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele * current_ele = polygone->first;

			distance = sqrt(pow(x - current_ele->p.x,2) + pow(y - current_ele->p.y, 2));

			min = distance;
			indice = 1;
			int i = 2;

			current_ele = current_ele->next;

			while(current_ele != NULL) {
				distance = sqrt(pow(x - current_ele->p.x,2) + pow(y - current_ele->p.y, 2));

				if(distance < min) {
					min = distance;
					indice = i;
				}
				i++;
				current_ele = current_ele->next;
			}
		}
	}
	return indice;
}

/**
 * display_polygone : Affiche les coordonnes des points d'un polygone
 * (utilise lors de debug)
 */
void display_polygone(poly *polygone) {
	printf("________________\n");
	printf("Polygone\n");
	if(polygone != NULL) {
		if(polygone->first != NULL) {
			ele *current_ele = polygone->first;

			if(polygone->nb == 1) {
				printf("x : %d - y : %d\n", current_ele->p.x, current_ele->p.y);
			}

			while(current_ele->next != NULL) {
				printf("x : %d - y : %d\n", current_ele->p.x, current_ele->p.y);
				current_ele = current_ele->next;
			}

			//affichage du dernier point
			printf("x : %d - y : %d\n", current_ele->p.x, current_ele->p.y);
		}
	}
	printf("________________\n");
}
