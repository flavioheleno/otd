#ifndef __MAP_H__
#define __MAP_H__

//definições do mapa

#include "defines.h"

//cor para o fundo do mapa
extern rgb background;

//caminho por onde os monstros irão andar
extern geometry path;

//inicializa os valores para cada detalhe do mapa
void initMap();

//libera a memória usada pela 'initMap'
void freeMap();

//desenha a grama na tela
void drawGrass();

//desenha o mapa na tela
void drawMap();

//detecta se houve uma colisão com o caminho
int haveMapCollision(int x, int y, int w, int h);

#endif
