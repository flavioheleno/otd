#include "map.h"
#include "geometry.h"
#include "texture.h"
#include "common.h"
#include "files.h"

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

//define a borda do mapa
#define MAP_BORDER 17

geometry path;

texture grass;

void initMap() {
	//carrega a textura de grama
	setString(&(grass.file), "images/scenario/grass.tga");
	LoadTGA(&grass);

	//inicialização do caminho (path)
	path.color.r = 253;
	path.color.g = 245;
	path.color.b = 230;
	path.num_points = 0;
	path.points = NULL;
	loadMap("data/scenario/map.txt", &path);
}

void freeMap() {
	freePoints(&path);
	freeTexture(&(grass.id));
}

void drawGrass() {
	int x, y;
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//cor de fundo
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//limpa toda a tela
	glClear(GL_COLOR_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
	//seleciona a textura
	setTexture(grass.id);
	for (y = 0; y < ceil(400 / 17) + 2; y++) {
		for (x = 0; x < ceil(600 / 17) + 1; x++) {
			drawTexture(17, 17);
			glTranslated(17, 0, 0);
		}
		glLoadIdentity();
		glTranslated(0, (17 * y), 0);
	}
	//deseleciona a textura
	unsetTexture();
}

void drawMap() {
	struct list *a, *p;
	point L1, L2;
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//desenha o 'path', caso ele exista
	if (path.num_points) {
		glColor3ub(path.color.r, path.color.g, path.color.b);
		a = path.points;
		p = (*a).next;
		while (p) {
			if ((*a).value.x <= (*p).value.x) {
				L1.x = (*a).value.x;
				L2.x = (*p).value.x;
			} else {
				L1.x = (*p).value.x;
				L2.x = (*a).value.x;
			}
			if ((*a).value.y >= (*p).value.y) {
				L1.y = (*a).value.y;
				L2.y = (*p).value.y;
			} else {
				L1.y = (*p).value.y;
				L2.y = (*a).value.y;
			}
			L1.x -= MAP_BORDER;
			L2.x += MAP_BORDER;
			L1.y += MAP_BORDER;
			L2.y -= MAP_BORDER;
			glRectd(L1.x, L1.y, L2.x, L2.y);
			a = p;
			p = (*p).next;
		}
	}
}

int haveMapCollision(int x, int y, int w, int h) {
	struct list *a, *p;
	point L1, L2, B1, B2;
	int collision = 0;
	a = path.points;
	p = (*a).next;
	B1.x = (x - (w / 2));
	B1.y = (y + (h / 2));
	B2.x = (x + (w / 2));
	B2.y = (y - (h / 2));
	while ((p) && (!collision)) {
		if ((*a).value.x <= (*p).value.x) {
			L1.x = (*a).value.x;
			L2.x = (*p).value.x;
		} else {
			L1.x = (*p).value.x;
			L2.x = (*a).value.x;
		}
		if ((*a).value.y >= (*p).value.y) {
			L1.y = (*a).value.y;
			L2.y = (*p).value.y;
		} else {
			L1.y = (*p).value.y;
			L2.y = (*a).value.y;
		}
		L1.x -= MAP_BORDER;
		L2.x += MAP_BORDER;
		L1.y += MAP_BORDER;
		L2.y -= MAP_BORDER;
		if ((L1.x <= B2.x) && (L2.x >= B1.x) && (L1.y >= B2.y) && (L2.y <= B1.y)) {
			collision = 1;
		}
		a = p;
		p = (*p).next;
	}
	return collision;
}
