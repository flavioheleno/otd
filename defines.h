#ifndef __DEFINES_H__
#define __DEFINES_H__

//nome da janela criada pelo OpenGL
#define WINDOW_NAME "wndTD"

//tamanho do mapa
#define MAP_WIDTH 600
#define MAP_HEIGHT 400

//quantidade de life
#define START_LIFE 120.0

//define uma estrutura para o ponto
typedef struct {
	int x;
	int y;
} point;

//define uma estrutura para o tamanho
typedef struct {
	int w;
	int h;
} size;

//define uma estrutura para a textura
typedef struct {
	char *file;
	unsigned int bpp;
	unsigned int width;
	unsigned int height;
	unsigned int id;
} texture;

//define uma estrutura para o sprite
struct sprite {
	texture tex;
	struct sprite *next;
};

//define uma estrutura para o desenho
typedef struct {
	int orientation;
	int state;
	struct sprite *sprite;
} draw;

//define uma estrutura para cores rgb
typedef struct {
	unsigned short r;
	unsigned short g;
	unsigned short b;
} rgb;

//define uma lista encadeada para pontos
struct list {
	point value;
	struct list *next;
};

//define uma estrutura para a geometria dos objetos
typedef struct {
	unsigned int num_points;
	struct list *points;
	rgb color;
} geometry;

//define uma estrutura para os monstros
typedef struct {
	char *name;
	unsigned int is_boss;
	unsigned int is_dead;
	float health;
	float life;
	float bounty;
	float speed;
	unsigned int space;
	draw view;
	size dimension;
	point position;
	float rotation;
	struct list *target;
} monster;

//define uma estrutura para os ataques
struct attack {
	monster m;
	struct attack *next;
};

//define uma estrutura para as ondas de ataque
typedef struct {
	int num_monsters;
	struct attack *monsters;
} wave; 

//define uma estrutura para as torres
typedef struct {
	char *name;
	unsigned int range;
	unsigned int power;
	float load_time;
	float cost;
	int level;
	texture view;
	point position;
	size dimension;
} tower;

//define uma estrutura para os elementos da defesa
struct defense_element {
	tower t;
	struct attack *target;
	float timeout;
	struct defense_element *next;
};

//define uma estrutura para a defesa
typedef struct {
	int num_towers;
	struct defense_element *towers;
} defense;

//define uma estrutura para a base
typedef struct {
	int health;
	texture view;
	size dimension;
	point position;
} base;

//define uma estrutura para o console
typedef struct {
	point position;
	size dimension;
} console;

//define uma estrutura para o tiro
struct shot {
	point position;
	point target;
	tower *t;
	monster *m;
	struct shot *next;
};

#endif
