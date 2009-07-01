#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "defines.h"

//carrega uma textura de um arquivo tga e carrega seus dados para uma estrutura
int LoadTGA(texture *t);

//adiciona uma textura a uma lista encadeada de texturas
void addTexture(draw *view, char *file);

//libera a memória usada por uma lista encadeada de texturas
void freeDraw(draw *view);

//libera a memória usada por uma textura
void freeTexture(unsigned int *id);

//seleciona uma textura para ser usada
void setTexture(unsigned int id);

//deseleciona a textura em uso
void unsetTexture();

//desenha um quadrado a partir da posição atual, com largura w e altura h, usando a textura selecionada
void drawTexture(int w, int h);

#endif
