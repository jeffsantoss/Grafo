#ifndef ARESTA_H
#define ARESTA_H

#include "Vertice.h"
#include <stdbool.h>

typedef struct aresta Aresta;

Aresta*		newAresta(char *chave, Vertice *v1, Vertice *v2, float peso);
void		setPesoAresta(Aresta *a, float novoValor);
void		DestruirAresta(Aresta *aresta);
char*		ChaveAresta(Aresta *aresta);
Vertice**	VerticeOrgDest(Aresta *aresta);
float		PesoAresta(Aresta *a);
void		ImprimeAresta(Aresta *aresta);

#endif