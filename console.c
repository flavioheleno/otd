#include "console.h"
#include "base.h"
#include "waves.h"
#include "defenses.h"
#include "shots.h"
#include "geometry.h"
#include "menu.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

console info;
console life;

int inConsole(int x, int y) {
	if ((info.position.x <= x) && (info.dimension.w >= x) && (info.position.y <= y) && (info.dimension.h >= y)) {
		return 1;
	} else {
		return 0;
	}
}

void initConsole() {
	info.position.x = 0;
	info.position.y = 0;
	info.dimension.w = 600;
	info.dimension.h = 60;

	life.position.x = 55;
	life.position.y = 43;
	life.dimension.w = 60;
	life.dimension.h = 13;
}

void drawConsole() {
	char temp[25];
	//muda para o modelview (altera apenas o desenho e não as coordenadas)
	glMatrixMode(GL_MODELVIEW);
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//movimenta o console
	glTranslated(info.position.x, info.position.y, 0);
	//desenha o console
	glColor3ub(0, 0, 0);
	glRectd(info.position.x, info.position.y, (info.position.x + info.dimension.w), (info.position.y + info.dimension.h));
	//desenha a barra de progresso de 'life'
	//muda a cor para branco
	glColor3ub(255, 255, 255);
	//desenha a borda
	glRectd(life.position.x, life.position.y, (life.position.x + life.dimension.w), (life.position.y + life.dimension.h));
	//muda a cor para a cor de fundo do console
	glColor3ub(0, 0, 0);
	//desenha o preenchimento
	glRectd((life.position.x + 1), (life.position.y + 1), (life.position.x + life.dimension.w - 1), (life.position.y + life.dimension.h - 1));
	if (home.health) {
		//muda a cor para a cor do life
		glColor3ub(255, 0, 0);
		//desenha a barra de progresso
		glRectd((life.position.x + 2), (life.position.y + 2), (life.position.x + ceil((life.dimension.w - 2) * (home.health / START_LIFE))), (life.position.y + life.dimension.h - 2));
	}
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//muda a cor para branco
	glColor3ub(255, 255, 255);
	//cabeçalho de 'life'
	drawText("Life:", 5, 45);
	//cabeçalho de 'money'
	sprintf(temp, "Money: $%.2f", money);
	drawText(temp, 5, 30);
	//cabeçalho de 'wave'
	sprintf(temp, "Wave: #%d", (current_wave + 1));
	drawText(temp, 5, 15);
	//cabeçalho de 'monsters'
	sprintf(temp, "Monsters: #%d", showing_monsters);
	drawText(temp, 130, 45);
	//cabeçalho de 'towers'
	sprintf(temp, "Towers: #%d", defenses.num_towers);
	drawText(temp, 130, 30);
	//cabeçalho de 'kills'
	sprintf(temp, "Kills: #%d", kills);
	drawText(temp, 130, 15);
}

void drawText(char *text, int x, int y) {
	int i;
	//garantir que o desenho seja com relação ao sistema de coordenadas
	glLoadIdentity();
	//muda a cor para branco
	glColor3ub(255, 255, 255);
	//move para (x, y)
	glRasterPos2i(x, y);
	for (i = 0; i < strlen(text); i++) {
		//desenha o caractere
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
	}
}
