#include "geometry.h"
#include <stdlib.h>

#include <stdio.h>
#include <math.h>

#define MATH_PI 3.1415926535897932384626433832795

void addPoint(geometry *draw, point p) {
	struct list *n, *l;
	n = (struct list*) malloc(sizeof(struct list));
	(*n).value = p;
	(*n).next = NULL;
	if ((*draw).points) {
		l = (*draw).points;
		while ((*l).next) {
			l = (*l).next;
		}
		(*l).next = n;
	} else {
		(*draw).points = n;
	}
	(*draw).num_points++;
}

void addXY(geometry *draw, int x, int y) {
	point p;
	p.x = x;
	p.y = y;
	addPoint(draw, p);
}

void freePoints(geometry *draw) {
	struct list *l, *p;
	l = (*draw).points;
	while (l) {
		p = l;
		l = (*l).next;
		free(p);
	}
}

void calcLinearIncrement(point distance, float speed, point *increment, float *angle) {
	(*angle) = atan2(distance.y, distance.x);
	//calcula o incremento em x
	if (distance.x != 0) {
		if (distance.x < 0) {
			//incremento negativo
			(*increment).x = -ceil(speed);
		} else {
			//incremento positivo
			(*increment).x = ceil(speed);
		}
		//se o incremento é maior que a distância, reduz o incremento
		if (abs(distance.x) < abs((*increment).x)) {
			(*increment).x = distance.x;
		}
	} else {
		(*increment).x = 0;
	}
	//calcula o incremento em y
	if (distance.y != 0) {
		if (distance.y < 0) {
			//incremento negativo
			(*increment).y = -ceil(speed);
		} else {
			//incremento positivo
			(*increment).y = ceil(speed);
		}
		//se o incremento é maior que a distância, reduz o incremento
		if (abs(distance.y) < abs((*increment).y)) {
			(*increment).y = distance.y;
		}
	} else {
		(*increment).y = 0;
	}
	//calcula a rotação conforme o caminho
	(*angle) = ((((*angle) / MATH_PI) * 180) - 90);
}

void calcAngularIncrement(point distance, float speed, point *increment, float *angle) {
	(*angle) = atan2(distance.y, distance.x);
	//calcula o incremento em x
	if (distance.x != 0) {
		(*increment).x = (speed * cos((*angle)));
		//se o incremento é maior que a distância, reduz o incremento
		if (abs(distance.x) < abs((*increment).x)) {
			(*increment).x = distance.x;
		}
	} else {
		(*increment).x = 0;
	}
	//calcula o incremento em y
	if (distance.y != 0) {
		(*increment).y = (speed * sin((*angle)));
		//se o incremento é maior que a distância, reduz o incremento
		if (abs(distance.y) < abs((*increment).y)) {
			(*increment).y = distance.y;
		}
	} else {
		(*increment).y = 0;
	}
	//calcula a rotação conforme o caminho
	(*angle) = ((((*angle) / MATH_PI) * 180) - 90);
}
