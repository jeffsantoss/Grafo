#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Aresta.h"
#include "Vertice.h"
#include "Grafo.h"

#define _VERTICE_ORIG 0	
#define _VERTICE_DEST 1
#define _SIZE_FILE 9999

void Relaxamento(Grafo *grafo, Vertice *org, Vertice *dest) {

	float distc = 0;

	Aresta *aresta = GetAresta(grafo, org, dest);

	distc = PesoVertice(org) + PesoAresta(aresta);

	if (distc < PesoVertice(dest)) {

		setPesoVertice(dest, distc);

		setPredecessor(dest, org);
	}

}

void CaminhoMinimo(Grafo *grafo, Vertice *org, Vertice *dest) {

	int CMindex = 0;

	Vertice **CaminhoMinimo = (Vertice**)malloc(Qtd_Vertices() * sizeof(Vertice*));
	Aresta  **arestasGrafo = GetArestas(grafo);
	Vertice *aux = dest;

	setPesoVertice(org, 0);

	for (int i = 0; i < Qtd_Vertices() - 1; i++)

		for (int j = 0; j < Qtd_Arestas(); j++) {

			Vertice **vertices = VerticeOrgDest(arestasGrafo[j]);

			Relaxamento(grafo, vertices[_VERTICE_ORIG], vertices[_VERTICE_DEST]);
			Relaxamento(grafo, vertices[_VERTICE_DEST], vertices[_VERTICE_ORIG]);
		}


	if (isinf(PesoVertice(dest)))
	{
		printf("Caminho inexistente \n");
		return;
	}
	
	/*
	else if (PesoVertice(dest) < 0) {
		printf("Houve um clico negativo \n");
		return;
	}
	*/

	while (aux != NULL) {

		CaminhoMinimo[CMindex] = aux;
		aux = getPredecessor(aux);
		CMindex++;

	}

	printf("\n >> Menor caminho do vertice (%s) ao (%s): ", ChaveVertice(org), ChaveVertice(dest));

	for (int k = CMindex - 1; k >= 0; k--) {
		printf(" %s - ", ChaveVertice(CaminhoMinimo[k]));
	}


	printf("\n >> Custo: ( %.2f ) \n", PesoVertice(dest));

}

void RestaurarGrafo(Grafo *grafo)
{
	int i, no_qtd = Qtd_Vertices(grafo);

	Vertice **vertices = GetVertices(grafo);

	for (i = 0; i < no_qtd; i++)
	{
		setPesoVertice(vertices[i], INFINITY);
		setPredecessor(vertices[i], NULL);
	}
}

void LerComando(Grafo *grafo, char *comando) {

	if (comando == NULL || grafo == NULL) {
		printf("Ocorreu um erro!");
		return;
	}

	char *syntax;

	if (comando[strlen(comando) - 1] = '\n');
	comando[strlen(comando) - 1] = '\0';

	/*
	 Strtok guarda na primeira chamada uma vari�vel est�tica a qual ele vai apontar
	 nas pr�ximas chamada, se for passado como par�metro nulo vai continuar na mesma chamada
	 at� ser passado outro ponteiro pra char.
	*/

	syntax = strtok(comando, " ");

	if (syntax == NULL)
		return;

	else if (!strcmp(syntax, "CV")) {

		const char *valorinserido = strtok(NULL, " ");

		if (VerticeExiste(grafo, valorinserido)) {
			printf("Vertice (%s) ja existente\n", valorinserido);
			return;
		}

		Vertice *verticeInserido = newVertice(valorinserido);

		InserirVertice(grafo, verticeInserido);
		printf("\n >> Vertice (%s) criado com sucesso \n", valorinserido);
		return;
	}
	else if (!strcmp(syntax, "RV")) {

		const char *valorremovido = strtok(NULL, " ");

		Vertice *verticeremovido = GetVerticePorChave(grafo, valorremovido);

		if (verticeremovido == NULL) {
			printf("Vertice (%s) nao encontrado", valorremovido);
			return;
		}

		RemoverVertice(grafo, verticeremovido);

		printf("\n >> Vertice (%s) removido com sucesso", valorremovido);
		return;

	}
	else if (!strcmp(syntax, "RA")) {

		char *valorremovido = strtok(NULL, " ");

		Aresta *arestaremovida = GetArestaPorChave(grafo, valorremovido);

		if (arestaremovida == NULL) {
			printf("\nAresta (%s) nao encontrada", valorremovido);
			return;
		}

		RemoverAresta(grafo, arestaremovida);
		printf("\n >> Aresta (%s) removida com sucesso", valorremovido);
		return;

	}
	else if (!strcmp(syntax, "CA")) {

		const char *valoreinserido = strtok(NULL, " ");
		const char *verticeOrigem = strtok(NULL, " ");
		const char *verticeDestino = strtok(NULL, " ");
		const char *arestaPeso = strtok(NULL, " ");

		Vertice *VerticeOrig = GetVerticePorChave(grafo, verticeOrigem);
		Vertice *VerticeDest = GetVerticePorChave(grafo, verticeDestino);

		if (VerticeOrig == NULL) {
			printf("\nVertice (%s) nao encontrados!", verticeOrigem);
			return;
		}
		else if (VerticeDest == NULL) {
			printf("\nVertice (%s) nao encontrados!", verticeDestino);
			return;
		}


		Aresta *aresta = newAresta(valoreinserido, VerticeOrig, VerticeDest, (float)atof(arestaPeso));

		if (ArestaExiste(grafo, aresta)) {

			printf(" ERRO ao inserir aresta (%s) ! \n", valoreinserido);
			DestruirAresta(aresta);

			return;
		}
		else 
		{
			InserirAresta(grafo, aresta);
		}

		printf("\n >> Aresta (%s) com peso (%.1f) coincidindo os vertices (%s) e (%s) "
			"inserido no grafo com sucesso! \n",
			valoreinserido, (float)atof(arestaPeso),
			verticeOrigem, verticeDestino);
		return;

	}
	else if (!strcmp(syntax, "IG")) {

		ImprimeGrafo(grafo);
		//teste(grafo);

		return;

	}
	else if (!strcmp(syntax, "TA")) {

		const char *valorAresta = strtok(NULL, " ");
		const char *novoPesoAresta = strtok(NULL, " ");
		Aresta *aresta = GetArestaPorChave(grafo, valorAresta);

		if (aresta == NULL) {
			printf("Aresta (%s) nao encontrada! ", valorAresta);
			return;
		}

		float pesoantigo = PesoAresta(aresta);

		setPesoAresta(aresta, (float)atof(novoPesoAresta));

		printf("\n >> Peso (%.1f) da aresta (%s) alterado para (%.1f)",
			pesoantigo, valorAresta, PesoAresta(aresta));

		return;
	}
	else if (!strcmp(syntax, "CM")) {

		const char *verticeOrigem = strtok(NULL, " ");
		const char *verticeDestino = strtok(NULL, " ");

		Vertice *VerticeOrig = GetVerticePorChave(grafo, verticeOrigem);
		Vertice *VerticeDest = GetVerticePorChave(grafo, verticeDestino);

		if (VerticeOrig == NULL || VerticeDest == NULL) {
			printf("Um dos vertices nao encontrados!");
			return;
		}


		CaminhoMinimo(grafo, VerticeOrig, VerticeDest);


		RestaurarGrafo(grafo);


		return;
	}
	else if (!strcmp(syntax, "FM")) {

		DestruirGrafo(grafo);

		printf("\t\t >> Grafo destruido! Encerrando programa.. ");
		system("pause");
		exit(1);
		return;

	}
	else if (!strcmp(syntax, "exit")) {
		return Menu(grafo);
	}
	else if (!strcmp(syntax, "?")) {
		printf("\n \t\t    CV v Cria um vertice com o identificador v"
			"\n\n \t\t    RV v Remove o vertice identificado por v"
			"\n\n \t\t    CA a v1 v2 x Cria uma aresta com o identificador a incidindo nos vertices de identificadores v1 e v2"
			"O valor armazenado na aresta e um numero inteiro especificado por x"
			"\n\n \t\t    RA a Remove a aresta identificada por a"
			"\n\n \t\t    TA a x Troca o valor armazenado na aresta de identificador a pelo valor x"
			"\n\n \t\t    IG imprime o grafo"
			"\n\n \t\t  CM v1 v2 Determina e imprime o caminho minimo entre o vertice"
			"de identificador v1 e o vertice de identificador v2. "
			"\n\n \t\t    FM Termina a execucao do seu programa e destroi o grafo "
			"\n\n \t\t    exit retorna ao menu");
		return;
	}

	printf("Comando invalido!");
}

int Arquivo(Grafo *grafo) {

	char *nomeArquivo = (char*)malloc(20 * sizeof(char));

	char info[_SIZE_FILE];

	//printf(">> Nome do arquivo: ");

	//gets(nomeArquivo);

	FILE *arq;



	arq = fopen("arquivoGrafo.txt", "r");

	strcpy(nomeArquivo, "arquivoGrafo.txt");

	if (!arq)
		printf("n�o foi possivel abrir o arquivo (%s)", nomeArquivo);
	else

		printf("\n\t  >> LENDO ARQUIVO %s.. \n", nomeArquivo);

	while ((fgets(info, sizeof(info), arq)) != NULL) {
		LerComando(grafo, info);
	}

	printf("\n\t  >> ARQUIVO LIDO COM SUCESSO ! \n", nomeArquivo);



	fclose(arq);

	getch();

	return Menu(grafo);
}

void Comando(Grafo *grafo) {

	char *entrada = malloc(50 * sizeof(char));

	while (true) {

		system("cls");

		printf("< '?' para ver a syntax > \n");

		printf("\n \t Comando >> ");

		fgets(entrada, 50, stdin);

		LerComando(grafo, entrada);

		getch();


	}
}

int Menu(Grafo *grafo) {

	int op;

	system("cls");

	printf("\t |================== DESENVOLVEDORES: JEFFERSON SANTOS & ARTUR LIMA  ========================|\n"
		"\t |=============================  FACULDADE FARIAS BRITO =====================================|\n"
		"\t |==============================  ESTRUTURA DE DADOS II  ====================================|\n"
		"\t |=====================================  GRAFOS  ============================================|\n");




	printf("\n\t\t\t\t     Escolha uma das opcoes abaixo! \n"
		"\n \t\t\t\t	1 - Entrada por aquivo"
		"\n \t\t\t\t	2 - Entrada por comando \n");

	printf("\n\n\t\t\t\t Digite aqui:  ");
	scanf("%d", &op);

	while (op < 1 || op > 2)
	{
		printf("\n\n\t\t\t\tEscolha uma opcao valida: ");
		scanf("%d", &op);
		fflush(stdin);
	}

	switch (op) {

	case 1: Arquivo(grafo);	break;
	case 2: Comando(grafo); break;

	default:
		return Menu(grafo);
	}

	return 0;
}