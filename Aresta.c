#include "Aresta.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _VERTICE_ORIG 0
#define _VERTICE_DEST 1

struct aresta
{
	int chave;
	float peso;
	Vertice **vertices;
};

Aresta* newAresta(int chave, Vertice *v1, Vertice *v2, float peso)
{
	Aresta *aresta = (Aresta*)malloc(sizeof(Aresta));

	aresta->chave = chave;

	aresta->vertices = (Vertice**)malloc(2 * sizeof(Vertice*));
	aresta->vertices[_VERTICE_ORIG] = v1;
	aresta->vertices[_VERTICE_DEST] = v2;

	aresta->peso = peso;

	if (aresta->vertices == NULL || aresta == NULL)
	{
		free(aresta->vertices);
		free(aresta);
		return NULL;
	}

	return aresta;
}

void DestruirAresta(Aresta *aresta)
{
	free(aresta->vertices);
	free(aresta);
}

int ChaveAresta(Aresta *aresta) {
	if (aresta == NULL)
		return -1;
	else
		return aresta->chave;

}

// aqui retorna 2 vertices.
Vertice** VerticeOrgDest(Aresta *aresta) {

	if (aresta == NULL)
		return NULL;
	else
		return aresta->vertices;
}

float PesoAresta(Aresta *a) {

	if (a == NULL)
		return INFINITY;
	else
		return a->peso;
}

void ImprimeAresta(Aresta *aresta) {

	if (aresta == NULL)
	{
		printf("Null");
		return;
	}

	printf(" \n"
		"Chave da aresta : %d \n"
		"peso da aresta : %f \n"
		"Vertice origem : %c \n"
		"Vertice destino : %c \n",
		aresta->chave, aresta->peso,
		ChaveVertice(aresta->vertices[_VERTICE_ORIG]),
		ChaveVertice(aresta->vertices[_VERTICE_DEST]));
}
