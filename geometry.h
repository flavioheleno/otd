#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

//definições das funções "geométricas"
//manipulação de pontos na estrutura 'geometry'
//de uso comum para 'monsters', 'towers', 'map', entre outros

#include "defines.h"

//adiciona um ponto no formato (x,y) usando a estrutura 'point'
void addPoint(geometry *draw, point p);

//adiciona um ponto no formato (x,y)
void addXY(geometry *draw, int x, int y);

//calcula o incremento e o angulo para movimentação de um objeto de maneira linear
void calcLinearIncrement(point distance, float speed, point *increment, float *angle);

//calcula o incremento e o angulo para movimentação de um objeto de maneira angular
void calcAngularIncrement(point distance, float speed, point *increment, float *angle);

//libera a memória alocada na estrutura 'geometry'
void freePoints(geometry *draw);

#endif
