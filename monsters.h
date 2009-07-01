#ifndef __MONSTERS_H__
#define __MONSTERS_H__

//definições sobre os monstros
//o objetivo de todo monstro é atacar a base

#include "defines.h"

//número de monstros existentes
#define MAX_MONSTERS 3

//memória para o tipo básico de monstros
extern monster monsters[MAX_MONSTERS];

//inicializa os valores para cada monstro
void initMonsters();

//libera a memória usada pela 'initMonsters'
void freeMonsters();

//desenha os monstros na tela
void drawMonster(monster *m);

//movimenta um monstro na tela
void moveMonster(monster *m, point to, float angle);

#endif
