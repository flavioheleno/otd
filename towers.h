#ifndef __TOWERS_H__
#define __TOWERS_H__

//definições das torres, elas formam a defesa
//o objetivo é acabar com as ondas de ataque

#include "defines.h"

//número de torres existentes
#define MAX_TOWERS 3

//número de níveis das torres
#define MAX_LEVEL 4

//memória para o tipo básico de torre
extern tower towers[MAX_TOWERS];

//inicializa os valores para cada torre
void initTowers();

//libera a memória usada pela 'initTowers'
void freeTowers();

//desenha o alcance de ataque da torre na tela
void drawRange(tower t);

//draws tower's level
void drawLevel(tower t);

//desenha as torres na tela
void drawTower(tower t);

//movimenta uma torre na tela
void moveTower(tower *t, point to);

#endif
