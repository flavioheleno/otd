#include "monsters.h"
#include "geometry.h"
#include "common.h"
#include "texture.h"
#include "files.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define MOVE_DOWN -180.0
#define MOVE_RIGHT -90.0
#define MOVE_UP 0.0
#define MOVE_LEFT 90.0

monster monsters[MAX_MONSTERS];

void drawLife(monster m, float life) {
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//movimenta as coordenadas para a localização do monstro
	glTranslated((m.position.x - (m.dimension.w / 2)), (m.position.y - (m.dimension.h / 2)), 0);
	//define a cor de fundo da barra
	glColor3ub(0, 0, 0);
	//desenha a barra de fundo
	glRectd(0, -4, 34, -1);
	//define a cor de preenchimento da barra
	glColor3ub(255, 0, 0);
	//se o life é maior que 0
	if (life > 0) {
		//desenha a barra preenchida
		glRectd(1, -2, (ceil(32 * life) + 1), -3);
	} else {
		//desenha a barra vazia
		glRectd(1, -2, 1, -3);
	}
	//restaura a cor original
	glColor3ub(255, 255, 255);
}

void initMonsters() {
	//inicialização de 'blob'
	printf("	BLOB: ");
	if (loadMonster("data/monsters/blob.txt", &monsters[0])) {
		printf("OK\r\n");
		setString(&(monsters[0].name), "blob");
		monsters[0].is_dead = 0;
		monsters[0].position.x = 0;
		monsters[0].position.y = 0;
		monsters[0].dimension.w = 34;
		monsters[0].dimension.h = 34;
		monsters[0].rotation = 0.0;
		monsters[0].target = NULL;
		monsters[0].view.orientation = 1;
		monsters[0].view.state = 0;
		addTexture(&(monsters[0].view), "images/monsters/blob/down/1.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/down/2.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/down/3.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/up/1.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/up/2.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/up/3.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/right/1.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/right/2.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/right/3.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/left/1.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/left/2.tga");
		addTexture(&(monsters[0].view), "images/monsters/blob/left/3.tga");
	} else {
		printf("ERROR\r\n");
	}

	//inicialização de 'golum'
	printf("	GOLUM: ");
	if (loadMonster("data/monsters/golum.txt", &monsters[1])) {
		printf("OK\r\n");
		setString(&(monsters[1].name), "golum");
		monsters[1].is_dead = 0;
		monsters[1].position.x = 0;
		monsters[1].position.y = 0;
		monsters[1].dimension.w = 34;
		monsters[1].dimension.h = 34;
		monsters[1].rotation = 0.0;
		monsters[1].target = NULL;
		monsters[1].view.orientation = 1;
		monsters[1].view.state = 0;
		addTexture(&(monsters[1].view), "images/monsters/golum/down/1.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/down/2.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/down/3.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/up/1.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/up/2.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/up/3.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/right/1.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/right/2.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/right/3.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/left/1.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/left/2.tga");
		addTexture(&(monsters[1].view), "images/monsters/golum/left/3.tga");
	} else {
		printf("ERROR\r\n");
	}

	//inicialização de 'frizz'
	printf("	FRIZZ: ");
	if (loadMonster("data/monsters/frizz.txt", &monsters[2])) {
		printf("OK\r\n");
		setString(&(monsters[2].name), "frizz");
		monsters[2].is_dead = 0;
		monsters[2].position.x = 0;
		monsters[2].position.y = 0;
		monsters[2].dimension.w = 34;
		monsters[2].dimension.h = 34;
		monsters[2].rotation = 0.0;
		monsters[2].target = NULL;
		monsters[2].view.orientation = 1;
		monsters[2].view.state = 0;
		addTexture(&(monsters[2].view), "images/monsters/frizz/down/1.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/down/2.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/down/3.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/up/1.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/up/2.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/up/3.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/right/1.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/right/2.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/right/3.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/left/1.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/left/2.tga");
		addTexture(&(monsters[2].view), "images/monsters/frizz/left/3.tga");
	} else {
		printf("ERROR\r\n");
	}
}

void freeMonsters() {
	int i;
	for (i = 0; i <= MAX_MONSTERS; i++) {
		freeString(monsters[i].name);
		freeDraw(&(monsters[i].view));
	}
}

int selectSprite(monster *m) {
	struct sprite *s;
	int i;
	s = (*m).view.sprite;
	//seleciona o tipo de sprite a ser usado
	if (floor((*m).rotation) == MOVE_UP) {
		for (i = 0; i < 3; i++) {
			s = (*s).next;
		}
	} else if (floor((*m).rotation) == MOVE_RIGHT) {
		for (i = 0; i < 6; i++) {
			s = (*s).next;
		}
	} else if (floor((*m).rotation) == MOVE_LEFT) {
		for (i = 0; i < 9; i++) {
			s = (*s).next;
		}
	}
	switch ((*m).view.state) {
		case 14:
		case 13:
		case 12:
		case 11:
		case 10: {
			s = (*s).next;
		}
		case 9:
		case 8:
		case 7:
		case 6:
		case 5: {
			s = (*s).next;
		}
	}
	//changes the orientation of movement
	if ((*m).view.state == 14) {
		(*m).view.orientation = -1;
	} else if ((*m).view.state == 0) {
		(*m).view.orientation = 1;
	}
	if ((*m).view.orientation > 0) {
		(*m).view.state++;
	} else if ((*m).view.orientation < 0) {
		(*m).view.state--;
	}
	return (*s).tex.id;;
}

void drawMonster(monster *m) {
	int id;
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//movimenta o monstro
	glTranslated(((*m).position.x - ((*m).dimension.w / 2)), ((*m).position.y - ((*m).dimension.h / 2)), 0);
	//desenha o monstro
	if ((*m).view.sprite) {
		id = selectSprite(m);
		setTexture(id);
		drawTexture((*(*m).view.sprite).tex.width, (*(*m).view.sprite).tex.height);
		unsetTexture();
		drawLife((*m), ((*m).health / (*m).life));
	}
}

void moveMonster(monster *m, point to, float angle) {
	(*m).position = to;
	(*m).rotation = angle;
}
