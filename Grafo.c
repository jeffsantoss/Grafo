#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Grafo.h"
#include "Vertice.h"
#include "Aresta.h"

#define _VERTICE_ORIG 0
#define _VERTICE_DEST 1

int _QTD_VERTICES = 0;
int _QTD_ARESTAS = 0;
int _QTD_MAX_VERTICES = 4;
int _QTD_MAX_ARESTAS = 4;

struct grafo
{
	Vertice **vertices;
	Aresta **arestas;
};

Grafo* newGrafo()
{
	Grafo *G = (Grafo*)malloc(sizeof(Grafo));

	G->vertices = (Vertice**)malloc(_QTD_MAX_VERTICES * sizeof(Vertice*));

	G->arestas = (Aresta**)malloc(_QTD_MAX_ARESTAS * sizeof(Aresta*));

	if (G->vertices == NULL || G->arestas == NULL)
	{
		free(G->vertices);
		free(G->arestas);
		free(G);
		return NULL;
	}

	return G;
}

void DestruirGrafo(Grafo *G)
{
	int i;

	if (G == NULL)
		return;

	for (i = 0; i < _QTD_VERTICES; i++)
		DestruirVertice(G->vertices[i]);
	
	for (i = 0; i < _QTD_ARESTAS; i++)
		DestruirAresta(G->arestas[i]);

	free(G->vertices);
	free(G->arestas);
	free(G);
}

int Qtd_Vertices()
{
	return _QTD_VERTICES;
}

int Qtd_Arestas()
{
	return _QTD_ARESTAS;
}

void InserirVertice(Grafo *G, Vertice *v)
{
	char chaveVertice = ChaveVertice(v),
		i = 0;

	if (G == NULL || v == NULL)
		return;

	for (i = 0; i < _QTD_VERTICES; i++) {
		if (ChaveVertice(G->vertices[i]) == chaveVertice)
			return;
		else
			continue;
	}

	Vertice **novo = G->vertices;

	if (_QTD_VERTICES == _QTD_MAX_VERTICES)
	{
		novo = (Vertice**)realloc(novo,_QTD_MAX_VERTICES * 4 * sizeof(Vertice*));
		
		G->vertices = novo;

		_QTD_MAX_VERTICES *= 4;
	}

	G->vertices[_QTD_VERTICES++] = v;

}

void InserirAresta(Grafo *G, Aresta *aresta)
{
	if (G == NULL || aresta == NULL)
		return;

	Aresta **novo = G->arestas;

	if (_QTD_ARESTAS == _QTD_MAX_ARESTAS)
	{
		novo = (Aresta**)realloc(novo,_QTD_MAX_ARESTAS * 4 * sizeof(Aresta*));
		
		G->arestas = novo;

		_QTD_MAX_ARESTAS *= 4;
	}

	G->arestas[_QTD_ARESTAS++] = aresta;
}

void RemoverVertice(Grafo *G, Vertice *V) {

	if (G == NULL || V == NULL)
		return;

	for (int i = 0; i < _QTD_VERTICES; i++) {
		if (G->vertices[i] == V) {

			// Ajustando a quantidade de aresta.
			for (int j = i; j < _QTD_VERTICES - 1; j++)
				G->vertices[j] = G->vertices[j + 1];

			--_QTD_ARESTAS;
				G->vertices[_QTD_VERTICES] = NULL;
					break;
		}
	}
}

void RemoverAresta(Grafo *G, Aresta *aresta) {
	if (G == NULL || aresta == NULL)
		return;
	
	for (int i = 0; i < _QTD_ARESTAS; i++) {
		if (G->arestas[i] == aresta) {

			// Ajustando a quantidade de aresta.
			for (int j = i; j < _QTD_ARESTAS - 1; j++) 
				G->arestas[j] = G->arestas[j + 1];

					--_QTD_ARESTAS;
						G->arestas[_QTD_ARESTAS] = NULL;
							break;
		}
	}
}

// arestas dado 2 v�rtices.

Aresta* GetAresta(Grafo *G, Vertice *v1, Vertice *v2) {

	int i;

	if (G != NULL || v1 != NULL || v2 != NULL) {

		for (i = 0; i < _QTD_ARESTAS ; i++) {

			Vertice **vertices = VerticeOrgDest(G->arestas[i]);

			if ((vertices[_VERTICE_ORIG] == v1 
			&&  vertices[_VERTICE_DEST] == v2)
			|| (vertices[_VERTICE_ORIG] == v2
			&&  vertices[_VERTICE_DEST] == v1))
				return G->arestas[i];

		}
	}

		return NULL;
}

// retorna um v�rtice espec�fico.
Vertice* GetVertice(Grafo *G,Vertice *v) {
	if (G != NULL) {
		for (int i = 0;i < _QTD_VERTICES;i++) {
			if (G->vertices[i] == v) {
				return G->vertices[i];
			}
		}
	}
		return NULL;	
}

// retorna todos os v�rtices do G.
Vertice** GetVertices(Grafo *G) {
	if (G != NULL)
		return G->vertices;
	
	return NULL;
}

// retorna todas as arestas do G
Aresta** GetArestas(Grafo *G) {
	if (G != NULL)
		return G->arestas;

	return NULL;
}

void ImprimeGrafo(Grafo *G) {

	int i = 0;
	if (G == NULL) {
		printf("G est� vazio!");
		return;
	}

	else {

		printf("\n   Print do G: \n\n"
			"Quantidade de v�rtices: %d \n"
			"Quantidade de Arestas: %d \n",
			_QTD_VERTICES,_QTD_ARESTAS );

		printf(" Print dos Vertices: \n\n");
		for (i = 0;i < _QTD_VERTICES; i++)
			ImprimeVertice(G->vertices[i]);

		printf(" Print das Arestas: \n\n");
		for (i = 0;i < _QTD_ARESTAS; i++)
			ImprimeAresta(G->arestas[i]);
	}

}