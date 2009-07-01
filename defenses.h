#ifndef __DEFENSES_H__
#define __DEFENSES_H__

//definições sobre as defesas
//a defesa é composta por diversas torres

#include "defines.h"
#include "towers.h"

//torres
extern defense defenses;

//detecta se houve uma colisão com a defesa
int haveDefenseCollision(int x, int y, int w, int h);

//inicializa os valores para a defesa
void initDefenses();

//libera a memória usada pela 'initDefenses'
void freeDefenses();

//try to select a tower from defense list
void selectDefense(int x, int y);

//atualiza a defesa
void updateDefense();

//desenha as defesas
void drawDefense();

#endif
