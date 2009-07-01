#include "texture.h"
#include "common.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//função retirada de: http://nehe.gamedev.net/lesson.asp?index=06
int LoadTGA(texture *t) {
	GLubyte TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	GLubyte TGAcompare[12];
	GLubyte header[6];
	GLubyte *data = NULL;
	GLuint bytesPerPixel;
	GLuint imageSize;
	GLuint temp;
	GLuint type = GL_RGBA;
	GLuint i;

	FILE *file = fopen((*t).file, "rb");
	//abertura e leitura inicial do cabeçalho do arquivo tga
	if (file == NULL ||
	fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||
	memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||
	fread(header, 1, sizeof(header), file) != sizeof(header)) {
		if (file == NULL)
			return 0;
		else {
			fclose(file);
			return 0;
		}
	}
	//cálculo do tamanho da imagem
	(*t).width  = ((header[1] * 256) + header[0]);
	(*t).height = ((header[3] * 256) + header[2]);
 	if (((*t).width <= 0) || ((*t).height <= 0) || ((header[4] != 24) && (header[4] != 32))) {
		fclose(file);
		return 0;
	}
	//bits por pixel
	(*t).bpp = header[4];
	bytesPerPixel = ((*t).bpp / 8);
	imageSize = ((*t).width * (*t).height * bytesPerPixel);
	//aloca a memória necessária para carregar a imagem
	data = (GLubyte *) malloc(imageSize);
	if(data == NULL ||
	fread(data, 1, imageSize, file) != imageSize)	{
		if(data != NULL)
			free(data);

		fclose(file);
		return 0;
	}
	for(i = 0; i < imageSize; i += bytesPerPixel) {
		temp = data[i];
		data[i] = data[(i + 2)];
		data[(i + 2)] = temp;
	}
	fclose (file);
	//gera um novo identificador para a nova textura
	glGenTextures(1, &((*t).id));
	//seleciona a nova textura
	glBindTexture(GL_TEXTURE_2D, (*t).id);
	//configura a textura
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	if ((*t).bpp == 24) {
		printf("bpp 24!!!\r\n");
		type = GL_RGB;
	}
	//atribui os dados lidos a nova textura
	glTexImage2D(GL_TEXTURE_2D, 0, type, (*t).width, (*t).height, 0, type, GL_UNSIGNED_BYTE, data);
	//libera a memória usada
	free(data);
	return 1;
}

void addTexture(draw *view, char *file) {
	struct sprite *n, *l;
	n = (struct sprite*) malloc(sizeof(struct sprite));
	setString(&((*n).tex.file), file);
	LoadTGA(&((*n).tex));
	(*n).next = NULL;
	if ((*view).sprite) {
		l = (*view).sprite;
		while ((*l).next) {
			l = (*l).next;
		}
		(*l).next = n;
	} else {
		(*view).sprite = n;
	}
}

void freeDraw(draw *view) {
	struct sprite *l, *p;
	l = (*view).sprite;
	while (l) {
		p = l;
		l = (*l).next;
		freeTexture(&((*p).tex.id));
		free(p);
	}
}

void freeTexture(unsigned int *id) {
	glDeleteTextures(1, id);
}

void setTexture(unsigned int id) {
	//seleciona a textura	glBindTexture(GL_TEXTURE_2D, id);
	//habilita texturas 2D
	glEnable(GL_TEXTURE_2D);
	//habilita o teste de alpha
	glEnable(GL_ALPHA_TEST);
	//seleciona o teste de alpha
	glAlphaFunc(GL_GREATER, 0.5f);
}

void drawTexture(int w, int h) {
	//garante que a textura será aplicada sobre um fundo branco
	glColor3ub(255, 255, 255);
	//desenha um quadrado aplicando a textura
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(w, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(w, h);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, h);
	glEnd();
}

void drawRepeat(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
		glTexCoord2f(w, 0.0f); glVertex2f(x + w, y);
		glTexCoord2f(w, h); glVertex2f(x + w, y + h);
		glTexCoord2f(0.0f, h); glVertex2f(x, y + h);
	glEnd();
}

void unsetTexture() {
	//desabilita o teste de alpha
	glDisable(GL_ALPHA_TEST);
	//desabilita texturas 2D
	glDisable(GL_TEXTURE_2D);
}
