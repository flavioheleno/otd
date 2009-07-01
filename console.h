#ifndef __CONSOLE_H__
#define __CONSOLE_H__

//definições referentes ao console
//onde as informações são exibidas

#include "defines.h"

extern console info;

//verifica se um ponto está dentro do console
int inConsole(int x, int y);

//inicializa os valores para o console
void initConsole();

//desenha o console na tela
void drawConsole();

//desenha um texto no console
void drawText(char *text, int x, int y);

#endif
