#define _CRT_SECURE_NO_WARNINGS

#include "Vertice.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct vertice
{
	char *chave;
	float peso;
	Vertice *pred;
};

Vertice* newVertice(char *chave)
{
	Vertice *vertice = (Vertice*)malloc(sizeof(Vertice));
	vertice->chave = (char*)malloc(strlen(chave)*sizeof(chave));

	strcpy(vertice->chave,chave);
	vertice->peso = INFINITY;
	vertice->pred = NULL;
	
	return vertice;
}

void DestruirVertice(Vertice *v) {

	if (v == NULL)
		return;

	free(v->pred);
	free(v->chave);
	free(v);
}

char* ChaveVertice(Vertice *v) {

	if (v == NULL)
		return -1;
	else
		return v->chave;
}

float PesoVertice(Vertice *v)
{
	if (v == NULL)
		return -1;
	else
		return v->peso;
}

void setPesoVertice(Vertice *v,float peso) {
	if (v == NULL)
		return;
	else
		v->peso = peso;
}

Vertice* getPredecessor(Vertice *v) {
	if (v == NULL)
		return NULL;

	return v->pred;
}

void setPredecessor(Vertice *v,Vertice *pred) {
	if (v == NULL)
		return;

	v->pred = pred;
}

void ImprimeVertice(Vertice *v)
{
	if (v == NULL)
	{
		printf("Null");
		return;
	}

	printf(" \n"
		"\t Identificador :	( %s ) \n"
		"\t          Peso :	( %.1f ) \n",
		v->chave, PesoVertice(v));
}
