#ifndef __SHOTS_H__
#define __SHOTS_H__

//definições sobre os tiros disparados pelas 'towers' com alvo nos 'monsters'

#include "defines.h"

//adiciona um novo tiro
void addShot(point position, point target, tower *t, monster *m);

//inicializa os valores para as estruturas de tiro
void initShots();

//libera a memória usada pela 'initShots'
void freeShots();

//movimenta os tiros na tela
void updateShots();

//desenha os tiros na tela
void drawShots();


#endif
