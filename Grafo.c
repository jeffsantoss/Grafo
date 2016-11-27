#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

	_QTD_VERTICES = 0;
	_QTD_ARESTAS = 0;
	_QTD_MAX_VERTICES = 4;
	_QTD_MAX_ARESTAS = 4;

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

	if (G == NULL || v == NULL)
		return;

	if (VerticeExiste(G, ChaveVertice(v)))
		return;

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

	if (ArestaExiste(G, ChaveVertice(aresta)))
		return;

	Aresta **novo = G->arestas;

	if (_QTD_ARESTAS == _QTD_MAX_ARESTAS)
	{
		novo = (Aresta**)realloc(novo, _QTD_MAX_ARESTAS * 4 * sizeof(Aresta*));

		G->arestas = novo;

		_QTD_MAX_ARESTAS *= 4;
	}

		G->arestas[_QTD_ARESTAS++] = aresta;
	
}

void RemoverVertice(Grafo *G, Vertice *V) {

	if (G == NULL || V == NULL)
		return;

	// excluo todas as aretas que esse vertice ta presente
	for (int j = 0; j < _QTD_ARESTAS; j++) {

		Vertice **org_dest = VerticeOrgDest(G->arestas[j]);
		if (org_dest[_VERTICE_ORIG] == V || org_dest[_VERTICE_DEST] == V) {

			printf("\n >> Aresta (%s) tambem foi excluida por coincidir no vertice (%s) ", ChaveAresta(G->arestas[j]),ChaveVertice(V));

				RemoverAresta(G, G->arestas[j]);
		}

	}

	for (int i = 0; i < _QTD_VERTICES; i++) {

		if (G->vertices[i] == V) {

			// Ajustando a quantidade de aresta.
			for (int j = i; j < _QTD_VERTICES - 1; j++)
				G->vertices[j] = G->vertices[j + 1];

			--_QTD_VERTICES;

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

// arestas dado 2 vértices.

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

// retorna um vértice específico.
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

Vertice* GetVerticePorChave(Grafo *G, char *chave) {

	if (chave == NULL) {
		printf("chave nao encontrada");
		return;
	}

	if (G != NULL) {

		for (int i = 0;i < _QTD_VERTICES;i++) {
			if (!strcmp((ChaveVertice(G->vertices[i])),chave)) {
				return G->vertices[i];
			}
		}
	}

	return NULL;
}

Aresta* GetArestaPorChave(Grafo *G, char *chave) {

	if (G != NULL) {

		for (int i = 0;i < _QTD_ARESTAS;i++) {
			if (!strcmp((ChaveAresta(G->arestas[i])), chave)) {
				return G->arestas[i];
			}
		}
	}

	return NULL;
}


// retorna todos os vértices do G.
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

bool VerticeExiste(Grafo *G,char *chave) {

	if (G != NULL) {
		for (int i = 0;i < _QTD_VERTICES;i++) {
			if (!(strcmp(ChaveVertice(G->vertices[i]),chave))){
				return true;
			}
		}
	}

	return false;
}

bool ArestaExiste(Grafo *G, char *chave) {

	if (G != NULL) {
		for (int i = 0;i < _QTD_ARESTAS;i++) {
			if (!(strcmp(ChaveAresta(G->arestas[i]), chave))) {
				return true;
			}
		}
	}

	return false;
}



void OrdenarVertices(Grafo *G)
{
	Vertice *aux;

	for (int i = 0; i < _QTD_VERTICES; i++)
	{
		for (int j = i + 1; j < _QTD_VERTICES; j++)
		{
			// i > j
			if ((strcmp(ChaveVertice(G->vertices[i]), ChaveAresta(G->vertices[j]))  >  0))

			{
				aux = G->vertices[i];
				G->vertices[i] = G->vertices[j];
				G->vertices[j] = aux;

			}
		}
	}


	//printf("\n\t Vertices Ordenados com sucesso! \n");
}

void OrdenarArestas(Grafo *G)
{
	Aresta *aux;

	for (int i = 0; i < _QTD_ARESTAS ; i++)
	{
		for (int j = i + 1; j < _QTD_ARESTAS; j++)
		{
			// i > j
			if ( (strcmp(ChaveAresta(G->arestas[i]), ChaveAresta(G->arestas[j]))  >  0 ))

			{
				aux = G->arestas[i];
				G->arestas[i] = G->arestas[j];
				G->arestas[j] = aux;

			}
		}
	}



	//printf("\n\t Arestas Ordenadas com sucesso! \n");
}


void ImprimeGrafo(Grafo *G) {

	int i = 0,
		j = 0;
	if (G == NULL) {
		printf("Grafo está vazio!");
		return;
	}

	else {

		printf("\n\t\t Dados do grafo: \n\n"
			"\tQuantidade de vertices :	( %d )\n"
			"\tQuantidade de arestas  :	( %d ) \n",
			_QTD_VERTICES,_QTD_ARESTAS );

		printf("\n\t\tDados dos Vertices presentes no grafo em ordem! \n");

		OrdenarVertices(G);

		for (i = 0;i < _QTD_VERTICES; i++) {
			ImprimeVertice(G->vertices[i]);

		}

		if (i == 0)
			printf("\n\t\t O grafo nao contem vertices! \n");

		printf("\n\t\tDados das arestas presentes no grafo: \n");

		OrdenarArestas(G);

		for (i = 0;i < _QTD_ARESTAS; i++)
			ImprimeAresta(G->arestas[i]);

		if (i == 0)
			printf("\n\t\t O grafo nao contem arestas! \n");

	}

}