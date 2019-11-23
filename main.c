
/*===============================================================*\

		Vendredi 25 septembre 2013

	Arash Habibi

	main.c

	Un programme equivalent à 02_glut.c et qui ne prend en compte
	que trois événements pour quitter le programme.

\*===============================================================*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdbool.h>

#include "include/Image.h"
#include "include/bresenham.h"
#include "include/polygone.h"
#include "include/scan_line.h"

Image *img;
poly *polygone;

//polygone fermer ou ouvert
bool closed = false;
//polygone rempli ou vide
bool filled = false;

//position du selecteur
int position = 1;
//utilise pour savoir dans quel direction deplace le vertex
int direction = -1;

//modes
bool insertion = true;
bool vertex = false;
bool edge = false;


//------------------------------------------------------------------
//	C'est le display callback. A chaque fois qu'il faut
//	redessiner l'image, c'est cette fonction qui est
//	appelee. Tous les dessins doivent etre faits a partir
//	de cette fonction.
//------------------------------------------------------------------

void display_CB() {
	glClear(GL_COLOR_BUFFER_BIT);

	//remplit l'image de noir pour "effacer"
	Color noir = {0, 0, 0};
	I_fill(img, noir);

	//fermeture du polygone
	//on ne peut que fermer le polygone s'il y a au moins 3 points
	if(closed && (polygone->nb > 2)) {
		I_bresenham(
			img,
			polygone->last->p.x, polygone->last->p.y,
			polygone->first->p.x, polygone->first->p.y
		);
	}

	//remplissage du polygone si le polygone est ferme
	if(filled && closed) {
		scan_line(img, polygone);
	}

	if(insertion) {
		//trace le polygone
		I_polygone(img, polygone);
	}
	else if(vertex) {
		//trace le polygone
		I_polygone(img, polygone);

		//si la position a une valeur valide
		if((position > 0) && (position <= polygone->nb))
			polygone_select(img, polygone, position);
	} else if (edge) {
		//trace le polygone
		I_polygone(img, polygone);

		//si la position a une valeur valide
		if((position > 0) && (position <= polygone->nb))
			polygone_select_edge(img, polygone, position);
	}
	I_draw(img);
	glutSwapBuffers();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir en fonction de la position de
// la souris (x,y), en fonction du bouton de la souris qui a été
// pressé ou relaché.
//------------------------------------------------------------------

void mouse_CB(int button, int state, int x, int y) {
	if((button==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN)) {
		if(insertion) {
			//insertion d'un point en fin de polygone en x et y
			insert_point(polygone, x, y);
		} else if(vertex && (polygone->nb > 0)) {
			//recherche du point le plus proche de x et y
			position = closestVertex(polygone, x, y);
		} else if(edge && (polygone->nb > 1)) {
			//recherche du segement le plus proche de x et y
			position = closestEdge(polygone, x, y, closed);
		}
	} else if((button==GLUT_MIDDLE_BUTTON) && (state==GLUT_DOWN)) {
		if(edge && (polygone->nb > 1)) {
			//division du segement selectionne en deux
			polygone_add_point_edge(polygone, position);
		}
	}

	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche (non-spéciale) du clavier.
//------------------------------------------------------------------

void keyboard_CB(unsigned char key, int x, int y) {
	switch(key)
	{
		case 27 : exit(1); break;
		case 'z' : I_zoom(img, 2.0); direction = -1; break;
		case 'Z' : I_zoom(img, 0.5); direction = -1; break;
		case 'u' : I_zoomInit(img); direction = -1; break;

		case 'f' :
			filled = !filled;
			direction = -1;
			break;

		case 'c' :
			closed = !closed;
			direction = -1;
			break;

		case 'i' :
			insertion = true;
			vertex = false;
			edge = false;
			direction = -1;
			break;

		case 'v' :
			insertion = false;
			vertex = true;
			edge = false;
			direction = -1;
			break;

		case 'e' :
			insertion = false;
			vertex = false;
			edge = true;
			direction = -1;
			break;

		case 127 : //touche suppr
			direction = -1;
			if(vertex && (polygone->nb > 0)) {
				if((position > 0) && (position <= polygone->nb))
					polygone_delete_point(polygone, position);
				//on reajuste la position du point selectionne
				if((size_t)position != 1) {
					position--;

				//si le polygone n'est pas vide
				} else if (polygone->nb != 0) {
					position = polygone->nb;
				//si le polygone est vide on reinitialise la position
				} else
					position = 1;
			}
			break;

		case 'm' :
			direction = -1;
			if(edge && (polygone->nb > 1)) {
				if((position > 0) && (position <= polygone->nb))
					polygone_add_point_edge(polygone, position);
			}
			break;

		default :
			direction = -1;
			fprintf(stderr,"keyboard_CB : %d : unknown key.\n",key);
			break;
		}

	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche spéciale (F1, F2 ... F12, home, end, insert,
// haut, bas, droite, gauche etc).
//------------------------------------------------------------------

void special_CB(int key, int x, int y) {
	switch(key)
	{
		case GLUT_KEY_UP :
			if(vertex && (polygone->nb > 0)) {
				if((position > 0) && (position <= polygone->nb))
					polygone_move(polygone, position, 2);
			} else
				direction = -1;
			break;

		case GLUT_KEY_DOWN :
			if(vertex && (polygone->nb > 0)) {
				if((position > 0) && (position <= polygone->nb))
					polygone_move(polygone, position,3);
			} else
				direction = -1;
			break;

		case GLUT_KEY_LEFT :
			if(vertex && (polygone->nb > 0)) {
				if((position > 0) && (position <= polygone->nb))
					polygone_move(polygone, position,0);
			} else
				direction = -1;
			break;

		case GLUT_KEY_RIGHT :
			if(vertex && (polygone->nb > 0)) {
				if((position > 0) && (position <= polygone->nb))
					polygone_move(polygone, position,1);
			} else
				direction = -1;
			break;

			case 105 : //page suivante
				direction = -1;
				if(vertex && (polygone->nb > 0)) {
					//si on est pas sur le dernier point du polygone
					if((size_t)position != polygone->nb) {
						position++;
					//sinon on reviens au debut du polygone
					} else
						position = 1;
				} else if(edge && (polygone->nb > 1)) {
					if((size_t)position != polygone->nb) {
						//si le polygone n'est pas ferme et qu'on est sur
						//l'avant dernier point
						if((position == polygone->nb-1) && !closed)
							//on mets le point au debut du polygone
							position = 1;
						else
							position++;
					} else
						position = 1;
				}
				break;

		case 104 : //page precedente
			direction = -1;
			if(vertex && polygone->nb > 0) {
				//si on est pas sur le premier point
				if((size_t)position != 1)
					position--;
				else
					//sinon on mets le selecteur au dernier point du polygone
					position = polygone->nb;
			} else if(edge && polygone->nb > 1) {
				if((size_t)position != 1)
					position--;
				else {
					if(closed)
						position = polygone->nb;
					else
						//selecteur sur l'avant dernier point
						position = polygone->nb-1;
				}
			}
			break;

		default :
			direction = -1;
			fprintf(stderr,"special_CB : %d : unknown key.\n",key);
			break;
	}
	glutPostRedisplay();
}

//------------------------------------------------------------------------

int main(int argc, char **argv) {
	if((argc!=3)&&(argc!=2)) {
		fprintf(stderr,"\n\nUsage \t: %s <width> <height>\nou",argv[0]);
		fprintf(stderr,"\t: %s <ppmfilename> \n\n",argv[0]);
		exit(1);
	}
	else {
		int largeur, hauteur;
		if(argc==2) {
			img = I_read(argv[1]);
			largeur = img->_width;
			hauteur = img->_height;
		} else {
			largeur = atoi(argv[1]);
			hauteur = atoi(argv[2]);
			img = I_new(largeur,hauteur);

			//initialise le polygone et ses points de bases s'ils existent
			polygone = create_polygone();
		}

		int windowPosX = 100, windowPosY = 100;

		glutInitWindowSize(largeur,hauteur);
		glutInitWindowPosition(windowPosX,windowPosY);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
		glutInit(&argc, argv);
		glutCreateWindow(argv[0]);

		glViewport(0, 0, largeur, hauteur);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glOrtho(0,largeur,hauteur,0,-1,1);

		glutDisplayFunc(display_CB);
		glutKeyboardFunc(keyboard_CB);
		glutSpecialFunc(special_CB);
		glutMouseFunc(mouse_CB);
		// glutMotionFunc(mouse_move_CB);
		// glutPassiveMotionFunc(passive_mouse_move_CB);

		glutMainLoop();

		return 0;
	}
}
