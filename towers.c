#include "towers.h"
#include "geometry.h"
#include "common.h"
#include "texture.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

tower towers[MAX_TOWERS];

void initTowers() {
	//nicialização de 'cannon'
	setString(&(towers[0].name), "cannon");
	towers[0].range = 50;
	towers[0].power = 3;
	towers[0].load_time = 0.5;
	towers[0].cost = 2.5;
	towers[0].level = 0;
	towers[0].position.x = 0;
	towers[0].position.y = 0;
	towers[0].dimension.w = 34;
	towers[0].dimension.h = 34;
	setString(&(towers[0].view.file), "images/towers/cannon.tga");
	LoadTGA(&(towers[0].view));

	//inicialização de 'launcher'
	setString(&(towers[1].name), "launcher");
	towers[1].range = 80;
	towers[1].power = 12;
	towers[1].load_time = 1.5;
	towers[1].cost = 5.0;
	towers[1].level = 0;
	towers[1].position.x = 0;
	towers[1].position.y = 0;
	towers[1].dimension.w = 34;
	towers[1].dimension.h = 34;
	setString(&(towers[1].view.file), "images/towers/launcher.tga");
	LoadTGA(&(towers[1].view));

	//inicialização de 'rocket'
	setString(&(towers[2].name), "rocket");
	towers[2].range = 110;
	towers[2].power = 45;
	towers[2].load_time = 2.0;
	towers[2].cost = 10.0;
	towers[2].level = 0;
	towers[2].position.x = 0;
	towers[2].position.y = 0;
	towers[2].dimension.w = 34;
	towers[2].dimension.h = 34;
	setString(&(towers[2].view.file), "images/towers/rocket.tga");
	LoadTGA(&(towers[2].view));
}

void freeTowers() {
	int i;
	for (i = 0; i < MAX_TOWERS; i++) {
		freeString(towers[i].name);
		freeTexture(&(towers[i].view.id));
	}
}

void drawRange(tower t) {
	float i;
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//movimenta a torre
	glTranslated(t.position.x, t.position.y, 0);
	//habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//cor preta
	glColor4ub(0, 0, 0, 3);
	//circunferência do alcance
	glBegin(GL_POLYGON);
	for (i = 0; i < 360; i+=0.1) {
		glVertex2f(((t.range + 2) * sin(i)), ((t.range + 2) * cos(i)));
	}
	glEnd();
	//cor avermelhada
	glColor4ub(255, 100, 100, 5);
	//circunferência do alcance
	glBegin(GL_POLYGON);
	for (i = 0; i < 360; i+=0.1) {
		glVertex2f((t.range * sin(i)), (t.range * cos(i)));
	}
	glEnd();
	//desabilita a transparência
	glDisable(GL_BLEND);
	glColor3ub(255, 255, 255);
}

void drawLevel(tower t) {
	int i;
	if (t.level) {
		//muda para o modelview (altera apenas o desenho e não as coordenadas)
		glMatrixMode(GL_MODELVIEW);
		//garantir que o desenho seja com relação ao sistema de coordenadas
		glLoadIdentity();
		//movimenta as coordenadas para a localização do monstro
		glTranslated((t.position.x - (t.dimension.w / 2)), (t.position.y - (t.dimension.h / 2)), 0);
		//define a cor de fundo da barra
		glColor3ub(0, 0, 0);
		//desenha os pontos de nivel
		for (i = 0; i < MAX_LEVEL; i++) {
			glRectd((5 * i), 0, (3 + (5 * i)), 3);
		}
		//define a cor de preenchimento dos pontos
		glColor3ub(0, 255, 0);
		//desenha os pontos de nível
		glBegin(GL_POINTS);
		for (i = 0; i < t.level; i++) {
			glVertex2i((1 + (5 * i)), 1);
		}
		glEnd();
		//restaura a cor original
		glColor3ub(255, 255, 255);
	}
}

void drawTower(tower t) {
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//movimenta a torre
	glTranslated((t.position.x - (t.dimension.w / 2)), (t.position.y - (t.dimension.h / 2)), 0);
	//desenha a torre
	setTexture(t.view.id);
	drawTexture(t.view.width, t.view.height);
	unsetTexture();
}

void moveTower(tower *t, point to) {
	(*t).position = to;
}
