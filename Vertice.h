#ifndef VERTICE_H
#define VERTICE_H

#include <stdbool.h>

typedef struct vertice Vertice;

Vertice*	newVertice(char *chave);
void		DestruirVertice(Vertice *v);
char*		ChaveVertice(Vertice *v);
float		PesoVertice(Vertice *v);
void		setPesoVertice(Vertice *v, float peso);
Vertice*	getPredecessor(Vertice *v);
void		setPredecessor(Vertice *v, Vertice *pred);
void		ImprimeVertice(Vertice *v);

#endif