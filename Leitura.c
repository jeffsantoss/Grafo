#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Grafo.h"
#include "Aresta.h"
#include "Vertice.h"





const char *fm = "FM";
const char *cm = "CM";
const char *ca = "CA";
const char *cv = "CV";
const char *ig = "IG";
const char *ta = "TA";
const char *ra = "RA";
const char *rv = "RV";


bool SyntaxPrompt(Grafo *grafo,const char *syntax)
{
if (strcmp(syntax, "help")) {

printf("====================================== MAIN SYNTAX ====================================\n\n"
"					CV v  \n"
"			Cria um vértice com o identificador v \n\n"
"					 RV v \n"
"			Remove o vértice identificado por v \n\n"
"					CA a v1 v2 x \n"
"			Cria uma aresta com o identificador 'a' \n"
"			incidindo nos vértices de identificadores v1 e v2.	\n\n"
"			O valor armazenado na aresta é um número inteiro especificado por 'x' \n\n"
"					RA a \n"
"			Remove a aresta identificada por a \n"
"					TA a x \n"
"			Troca o valor armazenado na aresta de identificador a pelo valor x	\n\n"
"					IG	\n"
"			Imprime o grafo na tela \n\n"
"					CM v1 v2	\n"
"			Determina e imprime o caminho mínimo entre \n"
"			o vértice de identificador v1 e o vértice de identificador v2. \n\n"
"					FM	\n"
"			Termina a execução do seu programa.Todas as estruturas dinâmicas devem \n"
"			ser desalocadas e seu programa deve encerrar.\n\n "
"==========================================================================================\n");
return true;
}

else if (strlen(syntax) > 2) {
	printf("Invaid command");
	return false;
}

	else if (strcmp(syntax, ca))
	return false;

	else if (!strcmp(syntax, fm))
	return false;

	else if (!strcmp(syntax, cm))
	return false;

	else if (strcmp(syntax, cv)) {
		CV(grafo);
	return true;
}
else if (!strcmp(syntax, ig))
return false;
else if (!strcmp(syntax, ta))
return false;
else if (!strcmp(syntax, ra))
return false;
else if (!strcmp(syntax, rv))
return false;
else
printf("Invalid command!");

}


void CV(Grafo *grafo) {

	int v = 0;

	printf(" value >");
	scanf_s("%d", &v);

	InserirVertice(grafo, v);

}

void removeVertice(char *syntax, char *v) {
if(InvalidsyntaxPrompt(syntax)) {
printf("Invaid command");
return;
}
}

void PrintGraph(char *syntax, Graph *gh) {
printGraph(gh);
}

*/