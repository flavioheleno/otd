#include "base.h"
#include "geometry.h"
#include "texture.h"
#include "common.h"

#include <string.h>
#include <GL/gl.h>
#include <GL/glut.h>

base home;

void initBase() {
	home.health = START_LIFE;
	home.dimension.w = 32;
	home.dimension.h = 32;
	home.position.x = 530;
	home.position.y = 370;
	setString(&(home.view.file), "images/scenario/base.tga");
	LoadTGA(&(home.view));
}

void freeBase() {
	freeTexture(&(home.view.id));
}

void drawBase() {
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//move a base para o ponto correto
	glTranslated((home.position.x - (home.dimension.w / 2)), (home.position.y - (home.dimension.h / 2)), 0);
	//desenha a base
	setTexture(home.view.id);
	drawTexture(home.view.width, home.view.height);
	unsetTexture();
}

void moveBase(point *from, point to) {
	(*from) = to;
}
