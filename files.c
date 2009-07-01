#include "files.h"
#include "common.h"
#include "geometry.h"

#include <stdio.h>

//file format: boss:life:bounty:speed:space
int loadMonster(char *file, monster *m) {
	FILE *f;
	int r;
	int type, space;
	float life, bounty, speed;
	f = fopen(file, "r");
	if (f) {
		//read file data
		r = fscanf(f, "%d:%f:%f:%f:%d", &type, &life, &bounty, &speed, &space);
		fclose(f);
		//checks if read was successful
		if (r == 5) {
			(*m).is_boss = type;
			(*m).health = life;
			(*m).life = life;
			(*m).bounty = bounty;
			(*m).speed = speed;
			(*m).space = space;
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

int loadTowers(char *file, tower *t) {
	return 0;
}

int loadMap(char *file, geometry *g) {
	addXY(g, 30, 400);
	addXY(g, 30, 230);
	addXY(g, 150, 230);
	addXY(g, 150, 350);
	addXY(g, 270, 350);
	addXY(g, 270, 150);
	addXY(g, 80, 150);
	addXY(g, 80, 80);
	addXY(g, 400, 80);
	addXY(g, 400, 270);
	addXY(g, 550, 270);
	addXY(g, 550, 400);
	return 1;
}
