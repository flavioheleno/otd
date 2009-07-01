#include "common.h"
#include <string.h>
#include <stdlib.h>

void setString(char **dest, char *text) {
	(*dest) = (char*) malloc(sizeof(char) * strlen(text));
	strcpy((*dest), text);
}

void freeString(char *dest) {
	free(dest);
	dest = NULL;
}
