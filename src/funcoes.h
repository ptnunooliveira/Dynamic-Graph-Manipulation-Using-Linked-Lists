/*****************************************************************//**
 * @file   funcoes.h
 * @brief  Ficheiro com declarações das funções utilizadas.
 * 
 * @author ptnunooliveira
 * @date   March 2025
 *********************************************************************/

#pragma once

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "antena.h"


 /**
  * @brief Função para ler um ficheiro binário e carregar os dados numa lista ligada.
  *
  * @param NomeFicheiro Nome do ficheiro a ler.
  * @param head Apontador para o início da lista.
  *
  * @return true se o ficheiro foi aberto com sucesso, false caso contr�rio.
  */
bool LerListasBinario(const char* NomeFicheiro, Antena** head);

/**
 * @brief Função para guardar uma lista ligada num ficheiro binário.
 *
 * @param NomeFicheiro Nome do ficheiro a guardar a lista.
 * @param head Apontador para o início da lista a ser guardada.
 *
 * @return true se guardado com sucesso, false caso contrário.
 */
bool GuardarListasBinario(const char* NomeFicheiro, Antena* head);

/**
 * @brief Função que lê o ficheiro .txt e cria lista ligada com as Antenas.
 *
 * @param NomeFicheiro Nome do ficheiro a ler.
 * @param head Apontador o início da lista das Antenas.
 *
 * @return true se foi aberto com sucesso, false caso contrário.
 */
bool LerFicheiro(const char* NomeFicheiro, Antena** head);

/**
 * @brief Função para gravar a matriz alterada num ficheiro de texto.
 *
 * @param NomeFicheiro Nome do ficheiro onde será guardada a informação.
 * @param head Apontador para o início da lista das Antenas.
 *
 * @return true se gravou com sucesso, false caso contrário.
 */
bool GravarFicheiro(const char* NomeFicheiro, Antena* head, Antena* headnefasto);

/**
 * @brief Função para criar uma Antena.
 *
 * @param Linha Coordenada da linha da Antena.
 * @param Coluna Coordenada da coluna da Antena.
 * @param tipoAntena Tipo de Antena.
 *
 * @return Apontador para a nova Antena.
 */
Antena* CriarAntena(int linha, int coluna, char tipoantena);

/**
 * @brief Função para inserir de forma ordenada uma Antena na lista ligada.
 *
 * @param head	Apontador para o início da lista das Antenas.
 * @param nova	Apontador para a nova Antena a introduzir.
 *
 * @return Apontador para o início da lista das Antenas.
 */
Antena* InserirAntena(Antena* head, Antena* nova);

/**
 * @brief Função para criar a lista de zonas nefastas com base nas Antenas existentes.
 *
 * @param head Apontador para o início da lista das Antenas.
 *
 * @return Apontador para o início da lista das zonas Nefastas.
 */
Antena* CriarZonasNefastas(Antena* head);

/**
 * @brief Função para mostrar a matriz no terminal.
 *
 * @param head Apontador para o início da lista das Antenas.
 * @param headnefasto Apontador para o início da lista das zonas Nefastas.
 *
 * @return 1 com sucesso, 0 caso contrário.
 */
bool MostrarMatriz(Antena* head, Antena* headnefasto);

/**
 * @brief Função para remover uma Antena da lista ligada.
 *
 * @param head Apontador para o início da lista.
 * @param linha Linha da Antena a ser removida.
 * @param coluna Coluna da Antena a ser removida.
 *
 * @return true se a Antena foi removida, false caso contrário.
 */
bool RemoverAntena(Antena** head, int linha, int coluna);


// ------------------------------------------------------------------------------ //

// FUN��ES TESTE


int mostrarLista(Antena* head);

int mostrarListaNEFASTOS(Antena* headnefasto);

void ImprimirConteudoBinario(const char* NomeFicheiro);
