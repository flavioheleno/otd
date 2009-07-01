#include "map.h"
#include "monsters.h"
#include "waves.h"
#include "towers.h"
#include "base.h"
#include "console.h"
#include "menu.h"
#include "defenses.h"
#include "shots.h"
#include "targets.h"
#include "texture.h"

#include <stdio.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glut.h>

//controle de jogo
int game_play = 0;
int game_pause = 0;

//janela criada pelo OpenGL
int wndGL = 0;

void checkGame() {
	//se todas as ondas de ataque já foram enviadas
	if (current_wave >= WAVES) {
		if (game_play) {
			//fim de jogo
			game_play = 0;
		}
		if (home.health > 0) {
			//você venceu
			printf("FIM DE JOGO!\r\n");
			printf("VOCE VENCEU!\r\n");
			glLoadIdentity();
			glColor3ub(0, 0, 0);
			glTranslated(160, 280, 0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'O');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'U');
			glLoadIdentity();
			glTranslated(170, 140, 0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'W');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'I');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'N');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
		} else {
			//você perdeu
			printf("FIM DE JOGO!\r\n");
			printf("VOCE PERDEU!\r\n");
			glLoadIdentity();
			glColor3ub(0, 0, 0);
			glTranslated(160, 280, 0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'O');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'U');
			glLoadIdentity();
			glTranslated(120, 140, 0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'O');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'E');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
		}
	}
}

//OpenGL idle/draw callback
void gl_draw() {
	usleep(25000);
	//desenha a grama
	drawGrass();
	//desenha o mapa
	drawMap();
	if (game_play) {
		if (!game_pause) {
			//movimenta os monstros
			updateWave();
			//atualiza a defesa
			updateDefense();
			//seleciona os alvos
			updateTargets();
			//movimenta os tiros
			updateShots();
		}
		//desenha os monstros
		drawWave();
		//desenha as torres
		drawDefense();
		//desenha os tiros
		drawShots();
	}
	//desenha a base
	drawBase();
	//desenha o item selecionado do menu
	if (item) {
		drawItem();
	}
	//desenha o console
	drawConsole();
	//desenha o menu
	drawMenu();
	//verifica se o jogo acabou
	checkGame();
	glutSwapBuffers();
}

//OpenGL resize callback
void gl_resize(GLsizei w, GLsizei h) {
	//evita divisão por zero
	if(h == 0)
		h = 1;

	//especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	//inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D (0.0f, MAP_WIDTH, 0.0f, (MAP_HEIGHT * (h / w)));
	else 
		gluOrtho2D (0.0f, (MAP_WIDTH * (w / h)), 0.0f, MAP_HEIGHT);
	glutSwapBuffers();
}

//OpenGL mouse callback
void gl_mouse(int button, int state, int x, int y) {
	//se o jogo está ativo
	if ((game_play) && (!game_pause)) {
		if (item) {
			if ((button == 0) && (state == 1)) {
				//se o mouse não está sobre o console
				if (!inConsole(x, (MAP_HEIGHT - y))) {
					addItem();
				}
			}
		} else {
			if ((button == 0) && (state == 1)) {
				if (inConsole(x, (MAP_HEIGHT - y))) {
					selectItem(x, (MAP_HEIGHT - y));
				} else {
					selectDefense(x, (MAP_HEIGHT - y));
				}
			}
		}
	}
}

//OpenGL motion callback
void gl_motion(int x, int y) {
	usleep(1500);
	//se o jogo está ativo
	if ((game_play) && (!game_pause)) {
		//se existe um item selecionado e o mouse está acima da posição do console
		if ((item) && (!inConsole(x, (MAP_HEIGHT - y)))) {
			//verifica se houve colisão
			if ((!haveMapCollision(x, (MAP_HEIGHT - y), (*item).dimension.w, (*item).dimension.h)) && (!haveDefenseCollision(x, (MAP_HEIGHT - y), (*item).dimension.w, (*item).dimension.h))) {
				//se não houve, movimenta o item
				moveItem(x, (MAP_HEIGHT - y));
			}
		}
	}
}

//OpenGL keyboard callback
void gl_keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: {
			unselectItem();
			break;
		}
		case 'q': {
			//liberação da memória alocada
			printf("Encerrando..\r\n");
			freeMap();
			printf("	MAP: OK\r\n");
			freeBase();
			printf("	BASE: OK\r\n");
			freeMonsters();
			printf("	MONSTERS: OK\r\n");
			freeTowers();
			printf("	TOWERS: OK\r\n");
			freeMenu();
			printf("	MENU: OK\r\n");
			freeWaves();
			printf("	WAVES: OK\r\n");
			freeDefenses();
			printf("	DEFENSES: OK\r\n");
			freeShots();
			printf("	SHOTS: OK\r\n");
			glutDestroyWindow(wndGL);
		}
		case 's': {
			game_play = 1;
			break;
		}
		case 'p': {
			if (game_play) {
				game_pause = !game_pause;
			}
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	//inicialização do opengl
	printf("Inicializando OpenGL..\r\n");
	glutInit(&argc, argv);
	glutInitWindowSize(MAP_WIDTH, MAP_HEIGHT);
	glutInitWindowPosition(500, 200);
	glutInitDisplayMode(GLUT_ALPHA | GLUT_DOUBLE | GLUT_RGBA | GLUT_ACCUM);
        wndGL = glutCreateWindow(WINDOW_NAME);
        glutSetWindowTitle("Tower defence");

	//inicializações
	printf("Carregando dados..\r\n");
	initMap();
	printf("	MAP: OK\r\n");
	initBase();
	printf("	BASE: OK\r\n");
	initMonsters();
	printf("	MONSTERS: OK\r\n");
	initTowers();
	printf("	TOWERS: OK\r\n");
	initConsole();
	printf("	CONSOLE: OK\r\n");
	initMenu();
	printf("	MENU: OK\r\n");
	initWaves();
	printf("	WAVES: OK\r\n");
	initDefenses();
	printf("	DEFENSES: OK\r\n");
	initShots();
	printf("	SHOTS: OK\r\n");

	//registrando callbacks
	printf("Iniciando graficos..\r\n");
	glutDisplayFunc(gl_draw);
	glutReshapeFunc(gl_resize);
	glutIdleFunc(gl_draw);
	glutMouseFunc(gl_mouse);
	glutPassiveMotionFunc(gl_motion);
	glutKeyboardFunc(gl_keyboard);

	//laço de jogo
	printf("Jogando..\r\n");
	glutMainLoop();
	return 0;
}
