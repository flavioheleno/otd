#ifndef __FILES_H__
#define __FILES_H__

#include "defines.h"

//loads monster data from file
int loadMonster(char *file, monster *m);

//loads tower data from file
int loadTower(char *file, tower *t);

//loads map data from file
int loadMap(char *file, geometry *p);

#endif
