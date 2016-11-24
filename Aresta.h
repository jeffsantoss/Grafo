#ifndef ARESTA_H
#define ARESTA_H

#include "Vertice.h"
#include <stdbool.h>

typedef struct aresta Aresta;

Aresta*		newAresta(int chave, Vertice *v1, Vertice *v2, float peso);
void		DestruirAresta(Aresta *aresta);
int			ChaveAresta(Aresta *aresta);
Vertice**	VerticeOrgDest(Aresta *aresta);
float		PesoAresta(Aresta *a);
void		ImprimeAresta(Aresta *aresta);

#endif