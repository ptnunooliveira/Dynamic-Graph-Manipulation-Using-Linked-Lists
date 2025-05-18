/*****************************************************************//**
 * @file   Funcoes.h
 * @brief  Ficheiro que cont�m as assinaturas das fun��es usadas em Funcoes.c.
 * 
 * @author ptnunooliveira
 * @date   May 2025
 *********************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "malloc.h"
#include "Grafos.h"
#include "Buscas.h"

#pragma region ANTENAS

 /**
  * @brief Função para criar uma Antena.
  *
  * @param linha Coordenada da linha da Antena.
  * @param coluna Coordenada da coluna da Antena.
  * @param tipoAntena Frequência da Antena.
  * @param id Número de identificação da Antena.
  * @param val Controlo de erros.
  *
  * @return Apontador para um tipo Antena.
  */
Antena* CriarAntena(int linha, int coluna, char tipoAntena, int* id, int* val);

/**
 * @brief Função para inserir uma Antena na respetiva lista.
 *
 * @param head Apontador do início da lista.
 * @param nova Antena que deseja-se inserir.
 * @param val Controlo de erros.
 *
 * @return Apontador do início da lista.
 */
Antena* InserirAntena(Antena* head, Antena* nova, int* val);

#pragma endregion

#pragma region ARESTAS

/**
 * @brief Função para criar uma Aresta.
 *
 * @param origem Apontador para a origem da aresta.
 * @param destinoID Numero de identificação da antena destino.
 * @param distancia Peso da Aresta.
 * @param val Controlo de erros.
 *
 * @return Apontador para um tipo Aresta.
 */
Arestas* CriarAresta(Antena* origem, int destinoID, int distancia, int* val);

/**
 * @brief Função para inserir uma Aresta na respetiva lista.
 *
 * @param head Apontador para o início da respetiva lista.
 * @param nova Apontador para a Aresta a inserir na lista.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início da lista.
 */
Arestas* InserirAresta(Arestas* head, Arestas* nova, int* val);

#pragma endregion

#pragma region GRAFO
/**
 * @brief Função para ligar as Arestas às respetivas Antenas de origem.
 *
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param arestasHead Apontador para o início da lista das Arestas.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início da lista das Antenas.
 */
Antena* LigarAntenasArestas(Antena* antenaHead, Arestas* arestasHead, int* val);

/**
 * @brief Função para calcular as Arestas.
 *
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param arestasHead Apontador para o início da lista das Arestas.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início da lista das Arestas.
 */
Arestas* CalcularArestas(Antena* antenaHead, Arestas* arestasHead, int* val);

/**
 * @brief Função que liga a variável id ao destino da Aresta.
 *
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início da lista das Antenas
 */
Antena* LigarAntenaDestinoAntenaId(Antena* antenaHead, int* val);

/**
 * @brief Função para Remover uma Antena e as respetivas Arestas do grafo.
 *
 * @param antenaHead Apontador para o início do grafo.
 * @param antenaid Identificador da Antena a ser removida.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início do grafo atualizado.
 */
Antena* RemoverAntena(Antena* antenaHead, int antenaID, int* val);

#pragma endregion

#pragma region FICHEIROS

/**
 * @brief Função para ler dados a partir de um ficheiro não binário.
 *
 * @param nomeFicheiro Nome do ficheiro a ser lido.
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param id Apontador para a variável de identificação das Antenas.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início da lista de Antenas.
 */
Antena* LerFicheiro(char* nomeFicheiro, Antena* antenaHead, int* id, int* val);

/**
 * @brief Função que permite gravar apenas a posição das Antenas num ficheiro não binário.
 *
 * @param nomeFicheiro Nome do ficheiro onde se pretende guardar a posição das Antenas.
 * @param antenaHead Apontador para o início da lista das Antenas.
 *
 * @return 0 em caso de sucesso
 */
int GravarFicheiro(char* nomeFicheiro, Antena* antenaHead);

/**
 * @brief Função para gravar os dados do grafo em ficheiro binário.
 *
 * @param nomeFicheiro Nome do ficheiro onde se pretende guarda a informação do grafo.
 * @param antenaHead Apontador para o início do grafo.
 * @param id Variável que contém quantas Antenas o grafo tem.
 *
 * @return 0 em caso de sucesso.
 */
int GravarFicheiroBinario(char* nomeFicheiro, Antena* antenaHead, int id);

/**
 * @brief Função para ler a informação do Grafo contida num ficheiro binário.
 *
 * @param nomeFicheiro Nome do ficheiro que contem a informação do grafo.
 * @param id Apontador para a variável que contem a identificação da Antena.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início do grafo.
 */
Antena* LerFicheiroBinario(char* nomeFicheiro, int* id, int* val);

#pragma endregion

#pragma region FUNÇÕES TESTE
// ----------------------------------------------------------------------------------
//									FUN��ES TESTE
// ----------------------------------------------------------------------------------


int mostrarLista(Antena* head);

int mostrarListaArestas(Arestas* head);

#pragma endregion
