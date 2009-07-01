#ifndef __COMMON_H__
#define __COMMON_H__

//definições das funções de acesso/uso comum

//aloca a memória necessária para atribuir 'text' a 'dest'
void setString(char **dest, char *text);

//libera a memória alocada em 'dest'
void freeString(char *dest);

#endif
