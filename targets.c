#include "targets.h"
#include "waves.h"
#include "defenses.h"
#include "shots.h"

#include <math.h>

//função que verifica se o alvo está dentro do alcance da torre
int inSight(point position, tower t) {
	float a, b, r;
	a = t.position.x;
	b = t.position.y;
	r = t.range;
	return (pow((position.x - a), 2) + pow((position.y - b), 2) <= pow(r, 2));
}

//função que busca o próximo alvo que está dentro do alcance da torre
struct attack* nextTarget(tower t, struct attack *atk) {
	struct attack *a;
	int f = 0;
	a = atk;
	while ((a) && (!f)) {
		if ((!(*a).m.is_dead) && (inSight((*a).m.position, t))) {
			f = 1;
		} else {
			a = (*a).next;
		}
	}
	return a;
}

void updateTargets() {
	struct defense_element *l;
	point shot;
	//se existem monstros na tela
	if (showing_monsters) {
		//se existem torres
		if (defenses.num_towers) {
			l = defenses.towers;
			while (l) {
				//verifica se o alvo corrente ainda está na mira e vivo
				//senão seleciona um novo alvo (se possível)
				if (((*l).target) && (!(*(*l).target).m.is_dead)) {
					if (!inSight((*(*l).target).m.position, (*l).t)) {
						(*l).target = nextTarget((*l).t, (*l).target);
					}
				} else {
					(*l).target = nextTarget((*l).t, monster_wave[current_wave].monsters);
				}
				//se existe um alvo
				if ((*l).target) {
					//se a torre já recarregou
					if ((*l).timeout <= 0) {
						shot.x = (*l).t.position.x;
						shot.y = (*l).t.position.y;
						addShot(shot, (*(*l).target).m.position, &((*l).t), &((*(*l).target).m));
						(*l).timeout = (*l).t.load_time;
					}
				}
				l = (*l).next;
			}
		}
	}
}
