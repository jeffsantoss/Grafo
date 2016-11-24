#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "Aresta.h"
#include "Vertice.h"

#define _VERTICE_ORIG 0
#define _VERTICE_DEST 1

void Relaxamento(Grafo *grafo, Vertice *org, Vertice *dest) {
	
	float distc = 0;
	Aresta *aresta = GetAresta(grafo, org, dest);

	distc = PesoVertice(org) + PesoAresta(aresta);

	if (distc < PesoVertice(dest)) {

		setPesoVertice(dest, distc);

		setPredecessor(dest, org);
	}

}

void CaminhoMinimo(Grafo *grafo,Vertice *org, Vertice *dest){

	Aresta **arestasGrafo = GetArestas(grafo);
		
	setPesoVertice(org, 0);

	for (int i = 0; i <  Qtd_Vertices() - 1 ; i++)

		for (int j = 0; j < Qtd_Arestas(); j++) {

			Vertice **vertices = VerticeOrgDest(arestasGrafo[j]);

			Relaxamento(grafo, vertices[_VERTICE_ORIG], vertices[_VERTICE_DEST]);
			Relaxamento(grafo, vertices[_VERTICE_DEST], vertices[_VERTICE_ORIG]);
		}


	for (Vertice *v = dest; v != NULL; v = getPredecessor(v))
		printf("Chave: %c \n",ChaveVertice(v));

	printf("Custo: %f ", PesoVertice(dest));

}

int main() {

	Grafo *graph = newGrafo();

	Vertice *v1 = newVertice('A');
	Vertice *v2 = newVertice('B');
	Vertice *v3 = newVertice('C');
	Vertice *v4 = newVertice('D');
	Vertice *v5 = newVertice('E');
	Vertice *v6 = newVertice('F');
	Vertice *v7 = newVertice('G');
	Vertice *v8 = newVertice('H');
	Vertice *v9 = newVertice('I');
	Vertice *v10 = newVertice('J');
	Vertice *v11 = newVertice('K');
	Vertice *v12 = newVertice('L');
	Vertice *v13 = newVertice('M');
	Vertice *v14 = newVertice('N');

	Aresta *edge1_5 = newAresta(101, v1, v5, 5);
	Aresta *edge1_6 = newAresta(102, v1, v6, 1);
	Aresta *edge1_12 = newAresta(103, v1, v12, 2);
	Aresta *edge2_3 = newAresta(104, v2, v3, 11);
	Aresta *edge2_5 = newAresta(105, v2, v5, 1);
	Aresta *edge2_9 = newAresta(106, v2, v9, 9);
	Aresta *edge3_4 = newAresta(107, v3, v4, 3);
	Aresta *edge3_6 = newAresta(108, v3, v6, 3);
	Aresta *edge3_7 = newAresta(109, v3, v7, 5);
	Aresta *edge3_10 = newAresta(110, v3, v10, 6);
	Aresta *edge4_7 = newAresta(111, v4, v7, 4);
	Aresta *edge4_14 = newAresta(112, v4, v14, 5);
	Aresta *edge5_8 = newAresta(113, v5, v8, 8);
	Aresta *edge6_7 = newAresta(114, v6, v7, 1);
	Aresta *edge6_9 = newAresta(115, v6, v9, 6);
	Aresta *edge6_13 = newAresta(116, v6, v13, 4);
	Aresta *edge8_9 = newAresta(117, v8, v9, 10);
	Aresta *edge8_13 = newAresta(118, v8, v13, 7);
	Aresta *edge10_11 = newAresta(119, v10, v11, 13);
	Aresta *edge10_12 = newAresta(120, v10, v12, 8);
	Aresta *edge11_13 = newAresta(121, v11, v13, 9);
	Aresta *edge11_14 = newAresta(122, v11, v14, 6);

	InserirVertice(graph, v1);
	InserirVertice(graph, v2);
	InserirVertice(graph, v3);
	InserirVertice(graph, v4);
	InserirVertice(graph, v5);
	InserirVertice(graph, v6);
	InserirVertice(graph, v7);
	InserirVertice(graph, v8);
	InserirVertice(graph, v9);
	InserirVertice(graph, v10);
	InserirVertice(graph, v11);
	InserirVertice(graph, v12);
	InserirVertice(graph, v13);
	InserirVertice(graph, v14);

	InserirAresta(graph, edge1_5);
	InserirAresta(graph, edge1_6);
	InserirAresta(graph, edge1_12);
	InserirAresta(graph, edge2_3);
	InserirAresta(graph, edge2_5);
	InserirAresta(graph, edge2_9);
	InserirAresta(graph, edge3_4);
	InserirAresta(graph, edge3_6);
	InserirAresta(graph, edge3_7);
	InserirAresta(graph, edge3_10);
	InserirAresta(graph, edge4_7);
	InserirAresta(graph, edge4_14);
	InserirAresta(graph, edge5_8);
	InserirAresta(graph, edge6_7);
	InserirAresta(graph, edge6_9);
	InserirAresta(graph, edge6_13);
	InserirAresta(graph, edge8_9);
	InserirAresta(graph, edge8_13);
	InserirAresta(graph, edge10_11);
	InserirAresta(graph, edge10_12);
	InserirAresta(graph, edge11_13);
	InserirAresta(graph, edge11_14);


	ImprimeGrafo(graph);

	printf("\n\n Caminho minimo >> ");

	CaminhoMinimo(graph, v1, v14);

	printf("ok");
	getch();

}