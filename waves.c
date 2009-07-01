#include "waves.h"
#include "monsters.h"
#include "base.h"
#include "map.h"
#include "geometry.h"

#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

int current_wave = 0;
int last_wave = -1;
int showing_monsters = 1;
int num_monsters = 1;
int dead_monsters = 0;
int wait_next = 0;
int kills = 0;

wave monster_wave[WAVES];

//adiciona um monstro na onda de ataque
void addMonster(struct attack **a, monster m);

//libera a memória ocupada por 'addMonster'
void freeAttack(struct attack *a);

void initWaves() {
	int w, m = 0, x;
	//inicializar todas as ondas de ataque
	for (w = 0; w < WAVES; w++) {
		//força uma "lista circular" com os monstros
		if (m == MAX_MONSTERS) {
			m = 0;
		}
		if (monsters[m].is_boss) {
			//onda de ataque de chefe
			monster_wave[w].num_monsters = BOSS_WAVE;
		} else {
			//onda de ataque normal
			monster_wave[w].num_monsters = NORMAL_WAVE;
		}
		monster_wave[w].monsters = NULL;
		for (x = 0; x < monster_wave[w].num_monsters; x++) {
			addMonster(&(monster_wave[w].monsters), monsters[m]);
		}
		m++;
	}
}

void freeWaves() {
	int i;
	struct attack *l, * p;
	for (i = 0; i < WAVES; i++) {
		l = monster_wave[i].monsters;
		while (l) {
			p = l;
			l = (*l).next;
			freeAttack(p);
		}
	}
}

void freeAttack(struct attack *a) {
	free(a);
	a = NULL;
}

void updateWave() {
	static int counter = 0;
	int i;
	monster *m;
	struct attack *a;
	point pos, dist, inc;
	float angle;

	//se ainda existe uma onda de ataque
	if (current_wave < WAVES) {
		//se a home ainda tem 'life'
		if (home.health) {
			a = monster_wave[current_wave].monsters;
			counter++;
			//se "space" chamadas foram feitas (a drawWave), adiciona um novo monstro a tela
			if (counter == (*a).m.space) {
				//se o número de monstros na tela é menor que a quantidade de monstros da onda de ataque
				if (showing_monsters < monster_wave[current_wave].num_monsters) {
					//adiciona mais um monstro a tela
					showing_monsters++;
				}
				counter = 0;
			}
			//laço entre os monstros que estão na tela
			for (i = 0; i < showing_monsters; i++) {
				m = &((*a).m);
				//se o monstro está vivo e ainda não chegou ao destino, atualiza a posição
				if ((!(*m).is_dead) && ((*m).target)) {
					pos = (*m).position;
					dist.x = ((*((*m).target)).value.x - pos.x);
					dist.y = ((*((*m).target)).value.y - pos.y);
					//verifica se chegou ao destino (target)
					if ((abs(dist.x) + abs(dist.y)) <= 1) {
						//muda o destino
						(*m).target = (*((*m).target)).next;
						if (!(*m).target) {
							//este monstro já chegou ao destino
							dead_monsters++;
							//diminui o 'life' da base pois o monstro chegou ao destino
							if ((*m).is_boss) {
								home.health -= 5;
							} else {
								home.health--;
							}
							//marca o monstro como morto
							(*m).is_dead = 1;
						}
					} else {
						//cacula os incrementos de movimento e o ângulo de rotação
						calcLinearIncrement(dist, (*m).speed, &inc, &angle);
						//adiciona o incremento do movimento
						pos.x += inc.x;
						pos.y += inc.y;
						//movimenta o monstro
						moveMonster(m, pos, angle);
					}
				}
				//se existe um próximo item na onda de ataque, vai para ele (comportamento de lista circular)
				if ((*a).next) {
					a = (*a).next;
				} else {
					a = monster_wave[current_wave].monsters;
				}
			}
			//se todos os monstros desta onda já morreram ou já chegaram ao destino
			if (dead_monsters == monster_wave[current_wave].num_monsters) {
				//vai para a próxima onda de ataque
				current_wave++;
				dead_monsters = 0;
				showing_monsters = 1;
				counter = 0;
			}
		}
	}
}

void drawWave() {
	int i;
	monster *m;
	struct attack *a;

	//se ainda existe uma onda de ataque
	if (current_wave < WAVES) {
		//se a home ainda tem 'life'
		if (home.health) {
			a = monster_wave[current_wave].monsters;
			//laço entre os monstros que estão na tela
			for (i = 0; i < showing_monsters; i++) {
				m = &((*a).m);
				//se o monstro está vivo e ainda não chegou ao destino
				if ((!(*m).is_dead) && ((*m).target)) {
					//desenha o monstro
					drawMonster(m);
				}
				a = (*a).next;
			}
		}
	}
}

void addMonster(struct attack **a, monster m) {
	struct attack *n, *l;
	n = (struct attack*) malloc(sizeof(struct attack));
	(*n).m = m;
	(*n).m.position = (*(path.points)).value;
	(*n).m.target = path.points;
	(*n).next = NULL;
	if ((*a)) {
		l = (*a);
		while ((*l).next) {
			l = (*l).next;
		}
		(*l).next = n;
	} else {
		(*a) = n;
	}
}
