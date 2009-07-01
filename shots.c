#include "shots.h"
#include "waves.h"
#include "defenses.h"
#include "geometry.h"
#include "menu.h"

#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

#define SHOT_SPEED 5

//tiros disparados
struct shot *bullets;

//função que verifica se o alvo está dentro do alcance do tiro
int inRange(point position, monster m) {
	float a, b, r;
	a = m.position.x;
	b = m.position.y;
	r = (m.dimension.h < m.dimension.w ? m.dimension.h : m.dimension.w);
	//equação geral da circunferência
	return (pow((position.x - a), 2) + pow((position.y - b), 2) <= pow(r, 2));
}

void addShot(point position, point target, tower *t, monster *m) {
	struct shot *n, *l;
	n = (struct shot*) malloc(sizeof(struct shot));
	(*n).position = position;
	(*n).target = target;
	(*n).t = t;
	(*n).m = m;
	(*n).next = NULL;
	if (bullets) {
		l = bullets;
		while ((*l).next) {
			l = (*l).next;
		}
		(*l).next = n;
	} else {
		bullets = n;
	}
}

void initShots() {
	bullets = NULL;
}

void freeShots() {
	struct shot *l, *p;
	l = bullets;
	while (l) {
		p = l;
		l = (*l).next;
		printf("free (%p)\r\n", p);
		//free(p);
	}
}

void updateShots() {
	struct shot *s, *l = NULL;
	point dist, inc;
	float angle;
	//se houveram disparos
	if (bullets) {
		s = bullets;
		while (s) {
			//movimenta o tiro
			dist.x = ((*s).target.x - (*s).position.x);
			dist.y = ((*s).target.y - (*s).position.y);
			//verifica se chegou ao destino
			if ((abs(dist.x) + abs(dist.y)) > 1) {
				//cacula os incrementos de movimento e o ângulo de rotação
				calcAngularIncrement(dist, SHOT_SPEED, &inc, &angle);
				//adiciona o incremento do movimento
				(*s).position.x += inc.x;
				(*s).position.y += inc.y;
				//vai para o próximo elemento
				l = s;
				s = (*s).next;
			} else {
				//verifica se o monstro está vivo
				if (!(*(*s).m).is_dead) {
					//verifica se o monstro está no alcance da "explosão"
					if (inRange((*s).position, (*(*s).m))) {
						//tira sangue do monstro
						(*(*s).m).health -= (*(*s).t).power;
						//verifica se o monstro morreu
						if ((*(*s).m).health <= 0) {
							(*(*s).m).is_dead = 1;
							money += (*(*s).m).bounty;
							dead_monsters++;
							kills++;
						}
					}
				}
				if (l) {
					(*l).next = (*s).next;
					free(s);
					s = (*l).next;
				} else {
					bullets = (*s).next;
					free(s);
					s = bullets;
				}
			}
		}
	}
}

void drawShots() {
	struct shot *s;
	int i;
	//se houveram disparos
	if (bullets) {
		//muda para o modelview (altera apenas o desenho e não as coordenadas)
		glMatrixMode(GL_MODELVIEW);
		s = bullets;
		while (s) {
			//garantir que o desenho seja com relação ao sistema de coordenadas
			glLoadIdentity();
			//define a cor do tiro para preto
			glColor3ub(0, 0, 0);
			//movimenta o tiro
			glTranslated((*s).position.x, (*s).position.y, 0);
			//desenha o tiro
			glBegin(GL_POLYGON);
			for (i = 0; i < 360; i++) {
				glVertex2f(sin(i), cos(i));
			}
			glEnd();
			//vai para o próximo elemento
			s = (*s).next;
		}
	}
}
