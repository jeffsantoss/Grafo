#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>
#include "Aresta.h"
#include "Vertice.h"

typedef struct grafo Grafo;

Grafo*		newGrafo();
void		DestruirGrafo(Grafo *G);
int			Qtd_Vertices();
int			Qtd_Arestas();
void		InserirVertice(Grafo *G, Vertice *v);
void		InserirAresta(Grafo *G, Aresta *aresta);
void		RemoverVertice(Grafo *G, Vertice *V);
void		RemoverAresta(Grafo *G, Aresta *aresta);
Vertice*	GetVertice(Grafo *G, Vertice *v);
Vertice**	GetVertices(Grafo *G);
Aresta**	GetArestas(Grafo *G);
Aresta*		GetAresta(Grafo *G, Vertice *v1, Vertice *v2);
void		ImprimeGrafo(Grafo *G);

#endif