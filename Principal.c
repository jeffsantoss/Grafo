#define _CRT_SECURE_NO_WARNINGS

#include "Grafo.h"
#include "Trabalho.h"

void main()
{

	system("color 0A");
	system("title Estrutura de dados Grafo");

	Grafo *grafo = newGrafo();

	Menu(grafo);

	printf("Programa abortado!");

	getch();
}
