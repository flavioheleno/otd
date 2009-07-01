#ifndef __MENU_H__
#define __MENU_H__

//definições do menu, que fica sobre o console
//onde as torres ficam disponíveis para serem compradas

#include "defines.h"

//dinheiro inicial
extern float money;

//item selecionado do menu
extern tower *item;

//inicializa os valores para o menu
void initMenu();

//libera a memória usada pela 'initMenu'
void freeMenu();

//desenha o menu na tela
void drawMenu();

//deseleciona o item selecionado
void unselectItem();

//seleciona um item do menu a partir de sua posição
void selectItem(int x, int y);

//move o item selecionado na tela
void moveItem(int x, int y);

//desenha o item selecionado na tela
void drawItem();

//adiciona o item selecionado na defesa
void addItem();

#endif
