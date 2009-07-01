#include "menu.h"
#include "console.h"
#include "towers.h"
#include "defenses.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define ITEM_SIZE 10

float money = 70.0;

tower *item;
tower itens[MAX_TOWERS];

void initMenu() {
	int i;
	point p;
	item = NULL;
	p.x = 290;
	p.y = 43;
	for (i = 0; i < MAX_TOWERS; i++) {
		itens[i] = towers[i];
		moveTower(&itens[i], p);
		p.x += 75;
	}
}

void freeMenu() {
	if (item) {
		unselectItem();
	}
}

void drawMenu() {
	int i;
	char temp[10];
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//muda a cor para branco
	glColor3ub(90, 90, 90);
	//divisores
	glBegin(GL_POINTS);
	for (i = 0; i < 60; i+=2) {
		glVertex2i(239, i);
	}
	glEnd();
	//muda a cor para branco
	glColor3ub(255, 255, 255);
	drawText("M", 250, 45);
	drawText("E", 250, 32);
	drawText("N", 250, 19);
	drawText("U", 250, 6);
	//desenha as torres no menu
	for (i = 0; i < MAX_TOWERS; i++) {
		drawTower(itens[i]);
		drawText(itens[i].name, itens[i].position.x - 20, 17);
		sprintf(temp, "$%.2f", itens[i].cost);
		drawText(temp, itens[i].position.x - 20, 5);
	}
}

void unselectItem() {
	if (item) {
		free(item);
		item = NULL;
	}
}

void selectItem(int x, int y) {
	int i = 0, f = 0;
	while ((i < MAX_TOWERS) && (!f)) {
		if (((x + ITEM_SIZE) >= itens[i].position.x) && ((x - ITEM_SIZE) <= (itens[i].position.x + itens[i].dimension.w)) && ((y + ITEM_SIZE) >= itens[i].position.y) && ((y - ITEM_SIZE) <= (itens[i].position.y + itens[i].dimension.h))) {
			item = (tower *) malloc(sizeof(tower));
			(*item) = itens[i];
			f = 1;
		}
		i++;
	}
}

void moveItem(int x, int y) {
	point p;
	if (item) {
		p.x = x;
		p.y = y;
		moveTower(item, p);
	}
}

void drawItem() {
	if (item) {
		drawRange((*item));
		drawTower((*item));
	}
}

void addItem() {
	struct defense_element *l, *n;
	if (item) {
		if (money >= (*item).cost) {
			money -= (*item).cost;
			n = (struct defense_element*) malloc(sizeof(struct defense_element));
			(*n).t = (*item);
			(*n).t.level = 1;
			(*n).target = NULL;
			(*n).timeout = 0;
			(*n).next = NULL;
			defenses.num_towers++;
			if (defenses.towers) {
				l = defenses.towers;
				while ((*l).next) {
					l = (*l).next;
				}
				(*l).next = n;
			} else {
				defenses.towers = n;
			}
			unselectItem();
		}
	}
}
