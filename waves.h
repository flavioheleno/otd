#ifndef __WAVES_H__
#define __WAVES_H__

//definições das ondas de ataque dos monstros

#include "defines.h"

#define WAVES 3
#define NORMAL_WAVE 35
#define BOSS_WAVE 2

//onda de ataque
extern int current_wave;
//número de monstros em exibição na tela
extern int showing_monsters;
//número de monstros mortos na onda atual
extern int dead_monsters;
//número de monstros mortos
extern int kills;

//monstros
extern wave monster_wave[WAVES];

//inicializa os valores para cada onda de ataque
void initWaves();

//libera a memória usada pela 'initWaves'
void freeWaves();

//movimenta as ondas de ataque na tela
void updateWave();

//desenha as ondas de ataque na tela
void drawWave();

#endif
