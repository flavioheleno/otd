#ifndef __BASE_H__
#define __BASE_H__

//definições referentes a base
//local que deve ser protegido pelas torres
//alvo dos monstros

#include "defines.h"

//dados da base
extern base home;

//inicializa os valores para a base
void initBase();

//libera a memória usada pela 'initBase'
void freeBase();

//desenha a base na tela
void drawBase();

//movimenta a base na tela
void moveBase(point *from, point to);

#endif
