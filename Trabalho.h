#ifndef TRABALHO_H
#define TRABALHO_H

#include "Aresta.h"
#include "Vertice.h"
#include "Grafo.h"

/* OPERA��ES DO CAMINHO MINIMO */
void Relaxamento(Grafo *grafo, Vertice *org, Vertice *dest);
void CaminhoMinimo(Grafo *grafo, Vertice *org, Vertice *dest);


/* OPERA��ES DA ENTRADA DO USU�RIO */

void LerComando(Grafo *grafo, char *comando);
void Arquivo(Grafo *grafo);
void Comando(Grafo *grafo);
int  Menu(Grafo *grafo);


#endif