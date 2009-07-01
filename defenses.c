#include "defenses.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

defense defenses;

int haveDefenseCollision(int x, int y, int w, int h) {
	struct defense_element *d;
	point L1, L2, B1, B2;
	int collision = 0;
	B1.x = (x - (w / 2));
	B1.y = (y + (h / 2));
	B2.x = (x + (w / 2));
	B2.y = (y - (h / 2));
	d = defenses.towers;
	while ((d) && (!collision)) {
		L1.x = ((*d).t.position.x - ((*d).t.dimension.w / 2));
		L1.y = ((*d).t.position.y + ((*d).t.dimension.h / 2));
		L2.x = ((*d).t.position.x + ((*d).t.dimension.w / 2));
		L2.y = ((*d).t.position.y - ((*d).t.dimension.h / 2));
		if ((L1.x <= B2.x) && (L2.x >= B1.x) && (L1.y >= B2.y) && (L2.y <= B1.y)) {
			collision = 1;
		}
		d = (*d).next;
	}
	return collision;
}

void drawTimeout(tower t, float timeout) {
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//movimenta as coordenadas para a localização da torre
	glTranslated((t.position.x - (t.dimension.w / 2)), (t.position.y - (t.dimension.h / 2)), 0);
	//define a cor de fundo da barra
	glColor3ub(0, 0, 0);
	//desenha a barra de fundo
	glRectd(0, -4, 34, -1);
	//define a cor de preenchimento da barra
	glColor3ub(0, 0, 255);
	//se o timeout é maior que 0
	if (timeout > 0) {
		//desenha a barra preenchida
		glRectd(1, -2, (33 - (ceil(32 * timeout) + 1)), -3);
	} else {
		//desenha a barra preenchida
		glRectd(1, -2, 33, -3);
	}
	//restaura a cor original
	glColor3ub(255, 255, 255);
}

void initDefenses() {
	defenses.num_towers = 0;
	defenses.towers = NULL;
}

void freeDefenses() {
	struct defense_element *l, *p;
	l = defenses.towers;
	while (l) {
		p = l;
		l = (*l).next;
		free(p);
	}
}

void selectDefense(int x, int y) {
}

void updateDefense() {
	struct defense_element *l;
	if (defenses.num_towers) {
		l = defenses.towers;
		while (l) {
			if ((*l).timeout > 0.0) {
				(*l).timeout -= 0.025;
			}
			l = (*l).next;
		}
	}
}

void drawDefense() {
	struct defense_element *l;
	if (defenses.num_towers) {
		l = defenses.towers;
		while (l) {
			drawTower((*l).t);
			drawLevel((*l).t);
			drawTimeout((*l).t, ((*l).timeout / (*l).t.load_time));
			l = (*l).next;
		}
	}
}
