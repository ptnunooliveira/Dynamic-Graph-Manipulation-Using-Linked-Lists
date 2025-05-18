/*****************************************************************//**
 * @file   Buscas.c
 * @brief  Ficheiro que contém os algoritmos necessários para a Depth First Traversal e Breadth First Traversal
 * 
 * @author ptnunooliveira
 * @date   May 2025
 *********************************************************************/
#pragma once

#include "Buscas.h"

/*

#pragma region STACK


int PushStack(int stack[], int antenaID, int* top) {

	if ((*top) < 0 || antenaID < 0)
		return -2;

	stack[++(*top)] = antenaID;

	return 0;
}

int RemoveStack(int stack[], int* top) {

	return stack[(*top)--];
}

int VerTopoStack(int stack[], int* top) {

	return stack[(*top)];
}

bool VerificarStackVazia(int stack[], int top) {
	
	if (top == -1) {
		return true;
	}
	
	return false;
}

#pragma endregion

*/

#pragma region ALGORITMOS DFT & BFT


/**
 * @brief Função que procura o apontador para a Antena a partir do id fornecido por parâmetro.
 * 
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param antenaID Número de identificação da Antena a encontrar.
 * 
 * @return Apontador para a Antena encontrada.
 */
Antena* ProcurarAntenaPeloID(Antena* antenaHead, int antenaID) {

	if (antenaHead == NULL) {
		return antenaHead;
	}

	Antena* aux = antenaHead;

	while (aux) {
		if (aux->id == antenaID) {
			return aux;
		}
		aux = aux->proxAntena;
	}

	return NULL;
}


/**
 * @brief Função para resetar o campo "visitado" da struct Antena.
 * 
 * @param antenaHead Apontador para o início da lista
 * 
 * @return True em caso de sucesso, False caso contrário.
 */
bool ResetarVisitados(Antena* antenaHead) {
	
	if (antenaHead == NULL)
		return false;
		
	Antena* aux = antenaHead;

	while (aux != NULL) {
		aux->visitado = 0;
		aux = aux->proxAntena;
	}

	return true;
}


/**
 * @brief Função para saber quantas Antenas existem com a mesma frequência.
 * 
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param atual Apontador para a Antena que queremos verificar a frequência.
 * 
 * @return N�mero de Antenas com aquela frequência.
 */
int NumeroAntenasMesmaFrequencia(Antena* antenaHead, Antena* atual) {
	
	if (antenaHead == NULL)
		return -1;

	Antena* aux = antenaHead;
	int contador = 0;

	while (aux != NULL) {
		if (aux->tipoAntena == atual->tipoAntena)
			contador++;
		aux = aux->proxAntena;
	}

	return contador;
}


/**
 * @brief Função recursiva que faz a travessia na profundidade.
 * 
 * @param antenaHead Apontador para o início do grafo.
 * @param antenaID Identificador da Antena onde começa a travessia.
 * 
 * @return 0 em caso de sucesso.
 */
int DepthFirstTraversal(Antena* antenaHead, int antenaID) {

	if (antenaHead == NULL)
		return -2;

	Antena* atual = ProcurarAntenaPeloID(antenaHead, antenaID);
	Arestas* aresta = atual->arestas;

	printf("Estou na antena: %d\n", antenaID);		// debug
	atual->visitado = 1;

	while (aresta != NULL) {

		if (aresta->destino->visitado == 0) {
			printf("Vou para a antena: %d\n", aresta->destino->id);
			DepthFirstTraversal(antenaHead, aresta->destinoID);
		}

		aresta = aresta->proxAresta;
	}

	return 0;
}


/**
 * @brief Função não recursiva que faz a travessia na largura.
 * 
 * @param antenaHead Apontador para o início do grafo.
 * @param antenaID Identificador da Antena onde começa a travessia.
 * 
 * @return 0 em caso de sucesso.
 */
int BreadthFirstTraversal(Antena* antenaHead, int antenaID) {

	if (antenaHead == NULL)
		return -2;

	int num;

	Antena* atual = ProcurarAntenaPeloID(antenaHead, antenaID);
	num = NumeroAntenasMesmaFrequencia(antenaHead, atual);
	int queue[10];
	int j = 1;

	queue[0] = atual->id;

	atual->visitado = 1;

	for (int i = 0; i < num;) {

		printf("Estou na antena: %d\n", atual->id);	// debug

		Arestas* aresta = atual->arestas;

		while (aresta != NULL) {
			if (aresta->destino->visitado == 0) {
				queue[j++] = aresta->destino->id;
				aresta->destino->visitado = 1;
			}
			aresta = aresta->proxAresta;
		}

		atual = ProcurarAntenaPeloID(antenaHead, queue[++i]);
	}

	return 0;
}


/**
 * @brief Função que mostra todos os caminhos possíveis entre duas Antenas
 * 
 * @param antenaHead Apontador para o início do Grafo
 * @param origemID Identificador da Antena de origem.
 * @param destinoID Identificador da Antena de destino.
 * @param distanciaPercorrida Distância percorrida em cada caminho.
 * 
 * @return Número de caminhos possíveis.
 */
int TodosCaminhosPossiveis(Antena* antenaHead, int origemID, int destinoID, int distanciaPercorrida) {

	int numeroCaminhos = 0;

	if (antenaHead == NULL)
		return -2;

	if (origemID == destinoID)
		return numeroCaminhos;
	
	Antena* origem = ProcurarAntenaPeloID(antenaHead, origemID);
	Arestas* arestaOrigem = origem->arestas;

	origem->visitado = 1;

	while(arestaOrigem != NULL) {

		// Se o destino da aresta j� foi visitado passa para a pr�xima
		if (arestaOrigem->destino->visitado == 1) {
			arestaOrigem = arestaOrigem->proxAresta;
			continue;
		}

		// Se chegar ao destino
		if (arestaOrigem->destino->id == destinoID) {
			printf("\n\nDistancia: %d\n\n", distanciaPercorrida + arestaOrigem->distancia);
			arestaOrigem = arestaOrigem->proxAresta;
			numeroCaminhos++;
			continue;
		}

		// Se o destino da aresta n�o foi visitado, visita
		if (arestaOrigem->destino->visitado == 0) {
			arestaOrigem->destino->visitado = 1;
			
			// Chama a fun��o novamente
			numeroCaminhos += TodosCaminhosPossiveis(antenaHead, arestaOrigem->destinoID, destinoID, distanciaPercorrida + arestaOrigem->distancia);
			arestaOrigem->destino->visitado = 0;
		}
		
		arestaOrigem = arestaOrigem->proxAresta;
	}

	// Retorna o n�mero de caminhos.
	return numeroCaminhos;
}



#pragma endregion