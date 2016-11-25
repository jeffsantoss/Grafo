#include "Aresta.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _VERTICE_ORIG 0
#define _VERTICE_DEST 1

struct aresta
{
	char *chave;
	float peso;
	Vertice **vertices;
};

Aresta* newAresta(char *chave, Vertice *v1, Vertice *v2, float peso)
{
	if (v1 == NULL || v2 == NULL)
		return NULL;

	Aresta *aresta = (Aresta*)malloc(sizeof(Aresta));
	aresta->chave = (char*)malloc(20 * sizeof(chave));

	strcpy(aresta->chave, chave);
	aresta->peso = peso;

	aresta->vertices = (Vertice**)malloc(2 * sizeof(Vertice*));
	aresta->vertices[_VERTICE_ORIG] = v1;
	aresta->vertices[_VERTICE_DEST] = v2;

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
	free(aresta->chave);
	free(aresta);
}

char* ChaveAresta(Aresta *aresta) {
	if (aresta == NULL)
		return -1;
	else
		return aresta->chave;
}

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

void setPesoAresta(Aresta *a, float novoValor) {
	if (a == NULL)
		return NULL;

	a->peso = novoValor;
}

void ImprimeAresta(Aresta *aresta) {

	if (aresta == NULL)
	{
		printf("Null");
		return;
	}

	printf(" \n"
		"\t Identificador   :	( %s )\n"
		"\t peso da aresta  :	( %.1f ) \n"
		"\t Vertice origem  :	( %s ) \n"
		"\t Vertice destino :	( %s )\n",
		aresta->chave, aresta->peso,
		ChaveVertice(aresta->vertices[_VERTICE_ORIG]),
		ChaveVertice(aresta->vertices[_VERTICE_DEST]));
}
