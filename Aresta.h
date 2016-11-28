#ifndef ARESTA_H
#define ARESTA_H

#include "Vertice.h"
#include <stdbool.h>

typedef struct aresta Aresta;

Aresta*		newAresta(char *chave, Vertice *v1, Vertice *v2, float peso);
void		DestruirAresta(Aresta *aresta);

void		setPesoAresta(Aresta *a, float novoValor);
float		PesoAresta(Aresta *a);

char*		ChaveAresta(Aresta *aresta);

Vertice**	VerticeOrgDest(Aresta *aresta);
void		ImprimeAresta(Aresta *aresta);

#endif