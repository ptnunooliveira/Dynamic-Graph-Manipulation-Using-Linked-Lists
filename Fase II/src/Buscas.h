/*****************************************************************//**
 * @file   Buscas.h
 * @brief  Ficheiro que contém as assinaturas usadas em Buscas.c
 * 
 * @author ptnunooliveira
 * @date   May 2025
 *********************************************************************/

#pragma once

#include "Funcoes.h"

/*
#pragma region STACK

int PushStack(int stack[], int antenaID, int* idAtual);

int RemoveStack(int stack[], int* top);

int VerTopoStack(int stack[], int* top);

bool VerificarStackVazia(int stack[], int top);

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
Antena* ProcurarAntenaPeloID(Antena* antenaHead, int antenaID);

/**
 * @brief Função recursiva que faz a travessia na profundidade.
 *
 * @param antenaHead Apontador para o início do grafo.
 * @param antenaID Identificador da Antena onde começa a travessia.
 *
 * @return 0 em caso de sucesso.
 */
int DepthFirstTraversal(Antena* antenaHead, int antenaID);

/**
 * @brief Função não recursiva que faz a travessia na largura.
 *
 * @param antenaHead Apontador para o início do grafo.
 * @param antenaID Identificador da Antena onde começa a travessia.
 *
 * @return 0 em caso de sucesso.
 */
int BreadthFirstTraversal(Antena* antenaHead, int antenaID);

/**
 * @brief Função para resetar o campo "visitado" da struct Antena.
 *
 * @param antenaHead Apontador para o início da lista
 *
 * @return True em caso de sucesso, False caso contrário.
 */
bool ResetarVisitados(Antena* antenaHead);

/**
 * @brief Função para saber quantas Antenas existem com a mesma frequência.
 *
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param atual Apontador para a Antena que queremos verificar a frequência.
 *
 * @return Número de Antenas com aquela frequência.
 */
int NumeroAntenasMesmaFrequencia(Antena* antenaHead, Antena* atual);

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
int TodosCaminhosPossiveis(Antena* antenaHead, int origemID, int destinoID, int distanciaPercorrida);

#pragma endregion
