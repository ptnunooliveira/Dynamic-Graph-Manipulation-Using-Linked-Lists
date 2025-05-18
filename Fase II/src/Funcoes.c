/*****************************************************************//**
 * @file   Funcoes.c
 * @brief  Implementação de funções para manipulação de grafos.
 * 
 * @author ptnunooliveira
 * @date   May 2025
 *********************************************************************/


#include "Funcoes.h"


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
Antena* CriarAntena(int linha, int coluna, char tipoAntena, int* id, int* val) {

	*val = 0;
	
	// Aloca espaço do tamanho do tipo Antena.
	Antena* a = malloc(sizeof(Antena));

	// Se não conseguir alocar espaço
	if (a == NULL) {
		*val = -1;
		return NULL;
	}
	
	a->id = *id;
	a->linha = linha;
	a->coluna = coluna;
	a->tipoAntena = tipoAntena;
	a->visitado = 0;
	a->proxAntena = NULL;
	a->arestas = NULL;

	(*id)++;

	return a;
}


/**
 * @brief Função para inserir uma Antena na respetiva lista.
 * 
 * @param head Apontador do início da lista.
 * @param nova Antena que deseja-se inserir.
 * @param val Controlo de erros.
 * 
 * @return Apontador do início da lista.
 */
Antena* InserirAntena(Antena* head, Antena* nova, int* val) {

	*val = 0;

	// Testes para validação dos parâmetros
	if (nova == NULL) {
		*val = -2;
		return head;
	}

	if (head == NULL) {
		head = nova;
		return head;
	}
	
	// Testes para verificar a posição de inserção
	if ((head->linha > nova->linha) || (head->linha == nova->linha && head->coluna > nova->coluna)) {
		nova->proxAntena = head;
		head = nova;
		return head;
	}

	// Se for repetida
	if ((head->linha == nova->linha) && (head->coluna == nova->coluna)) {
		free(nova);
		*val = -3;
		return head;
	}

	// Criação de variáveis auxiliares
	Antena* frente = head;
	Antena* tras = frente;

	while ((frente->linha < nova->linha) || (frente->linha == nova->linha && frente->coluna < nova->coluna)) {
		
		// Se for repetida
		if ((frente->linha == nova->linha) && (frente->coluna == nova->coluna)) {
			free(nova);
			*val = -3;
			return head;
		}
		if (frente->proxAntena == NULL) {
			frente->proxAntena = nova;
			return head;
		}
		tras = frente;
		frente = frente->proxAntena;
	}
	nova->proxAntena = frente;
	tras->proxAntena = nova;
	
	return head;
}

#pragma endregion


#pragma region ARESTAS

/**
 * @brief Função para criar uma Aresta.
 * 
 * @param origem Apontador para a origem da aresta.
 * @param destinoID Número de identificação da antena destino.
 * @param distancia Peso da Aresta.
 * @param val Controlo de erros.
 * 
 * @return Apontador para um tipo Aresta.
 */
Arestas* CriarAresta(Antena* origem, int destinoID, int distancia, int* val){

	*val = 0;

	// Aloca espaço de tamanho do tipo Antena.
	Arestas* a = malloc(sizeof(Arestas));
	
	// Se não foi possível alocar espaço
	if (a == NULL) {
		*val = -1;
		return NULL;
	}

	a->destinoID = destinoID;
	a->origem = origem;
	a->destino = NULL;
	a->distancia = distancia;
	a->proxAresta = NULL;

	return a;
}


/**
 * @brief Função para inserir uma Aresta na respetiva lista.
 * 
 * @param head Apontador para o início da respetiva lista.
 * @param nova Apontador para a Aresta a inserir na lista.
 * @param val Controlo de erros.
 * 
 * @return Apontador para o início da lista.
 */
Arestas* InserirAresta(Arestas* head, Arestas* nova, int* val) {

	*val = 0;

	// Testes para validação dos parâmetros
	if (nova == NULL) {
		*val = -2;
		return head;
	}
	
	if (head == NULL) {
		head = nova;
		return head;
	}

	// Testes para verificar a posição de inserção
	if ((head->origem->linha > nova->origem->linha) || (head->origem->linha == nova->origem->linha && head->origem->coluna > nova->origem->coluna)) {
		nova->proxAresta = head;
		head = nova;
		return head;
	}

	// Criação de variáveis auxiliares
	Arestas* frente = head;
	Arestas* tras = frente;

	// Se a origem for a mesma que o head
	if ((frente->origem->linha == nova->origem->linha) && (frente->origem->coluna == nova->origem->coluna)) {

		// E o destino o mesmo, ou seja, repetida
		if (frente->destinoID == nova->destinoID) {
			*val = -3;
			free(nova);
			return head;
		}

		// Ordenar por distância
		while (frente != NULL && (frente->distancia < nova->distancia)) {
			tras = frente;
			frente = frente->proxAresta;
		}
		nova->proxAresta = frente;
		tras->proxAresta = nova;

		return head;
	}

	// Ordenar por linha, coluna e distância
	while ((frente->origem->linha < nova->origem->linha) || ((frente->origem->linha == nova->origem->linha) && (frente->origem->coluna < nova->origem->coluna))) {
		
		// Colocar na última posição
		if (frente->proxAresta == NULL) {
			frente->proxAresta = nova;
			return head;
		}

		tras = frente;
		frente = frente->proxAresta;

		// Se a origem for igual
		if ((frente->origem->linha == nova->origem->linha) && (frente->origem->coluna == nova->origem->coluna)) {

			// Comparar distância
			while (frente != NULL && (frente->distancia < nova->distancia)) {
				tras = frente;
				frente = frente->proxAresta;
			}

			nova->proxAresta = frente;
			tras->proxAresta = nova;
			return head;
		}
	}
	nova->proxAresta = frente;
	tras->proxAresta = nova;

	return head;
}

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
Antena* LigarAntenasArestas(Antena* antenaHead, Arestas* arestasHead, int* val) {

	*val = 0;

	// Se alguma lista estiver vazia
	if (antenaHead == NULL || arestasHead == NULL) {
		*val = -2;
		return antenaHead;
	}

	Antena* antenaAtual = antenaHead;
	Arestas* arestaAtual = arestasHead;

	// Percorre ambas as listas 
	while (antenaAtual != NULL && arestaAtual != NULL) {

		int duplicado = 0;		// Variável para verificar duplicados

		// Testar duplicados
		Arestas* teste = antenaAtual->arestas;
		while (teste != NULL) {
			if ((arestaAtual->origem->linha == antenaAtual->linha) && (arestaAtual->origem->coluna == antenaAtual->coluna) && (arestaAtual->destinoID == teste->destinoID)) {
				duplicado = 1;
				break;
			}
			teste = teste->proxAresta;
		}
		
		// Se for duplicado
		if (duplicado) {
			Arestas* tmp = arestaAtual;
			arestaAtual = arestaAtual->proxAresta;
			free(tmp);
			continue;
		}

		// Se a aresta for da antena
		if (arestaAtual->origem->linha == antenaAtual->linha && arestaAtual->origem->coluna == antenaAtual->coluna) {

			Arestas* proxima = arestaAtual->proxAresta;
			arestaAtual->proxAresta = NULL;

			// Se a lista das arestas da antena estiver vazia, inserir na primeira posição
			if (antenaAtual->arestas == NULL) {
				antenaAtual->arestas = arestaAtual;
			}
			// Inserir no fim da lista das arestas da respetiva antena
			else {
				Arestas* temp = antenaAtual->arestas;
				while (temp->proxAresta != NULL) {
					temp = temp->proxAresta;
				}
				temp->proxAresta = arestaAtual;
			}

			arestaAtual = proxima;
		}

		else {
			antenaAtual = antenaAtual->proxAntena;
		}
	}

	antenaHead = LigarAntenaDestinoAntenaId(antenaHead, val);
	return antenaHead;
}


/**
 * @brief Função para calcular as Arestas.
 * 
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param arestasHead Apontador para o início da lista das Arestas.
 * @param val Controlo de erros.
 * 
 * @return Apontador para o início da lista das Arestas.
 */
Arestas* CalcularArestas(Antena* antenaHead, Arestas* arestasHead, int* val) {

	*val = 0;

	// Testes para validação dos parâmetros
	if (antenaHead == NULL) {
		*val = -2;
		return arestasHead;
	}

	// Criação de variáveis de auxilio na procura
	Antena* aux = antenaHead;
	Antena* aux2 = aux;

	// Ciclos para percorrer a lista de antenas
	while (aux != NULL) {
		while (aux2 != NULL) {

			// Se for a mesma antena
			if (aux == aux2) {
				aux2 = aux2->proxAntena;
				continue;
			}

			// Se for a mesma frequência
			if (aux->tipoAntena == aux2->tipoAntena) {
				Arestas* nova = malloc(sizeof(Arestas));
				if (nova == NULL) {
					*val = -1;
					return arestasHead;
				}

				// Cálculo da distância
				int dis = (abs(aux->linha - aux2->linha)) + (abs(aux->coluna - aux2->coluna));

				// Criação e inserção da Aresta.
				nova = CriarAresta(aux, aux2->id, dis, val);
				arestasHead = InserirAresta(arestasHead, nova, val);
			}
			aux2 = aux2->proxAntena;
		}
		aux2 = antenaHead;
		aux = aux->proxAntena;
	}

	return arestasHead;
}


/**
 * @brief Função que liga a variável id ao destino da Aresta.
 *
 * @param antenaHead Apontador para o início da lista das Antenas.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início da lista das Antenas
 */
Antena* LigarAntenaDestinoAntenaId(Antena* antenaHead, int* val) {

	*val = 0;

	// Se a lista estiver vazia
	if (antenaHead == NULL) {
		*val = -2;
		return NULL;
	}

	Antena* auxAntena = antenaHead;

	// Enquanto houver Antenas
	while (auxAntena != NULL) {
		Arestas* auxArestas = auxAntena->arestas;

		// Enquanto houver Arestas naquela Antena
		while (auxArestas != NULL) {
			Antena* aux2antena = antenaHead;  // Variável secundária para percorrer a lista das Antenas

			// Enquanto houver Antenas
			while (aux2antena != NULL) {

				// Se o id da Antena corresponder ao id de destino das Arestas
				if (aux2antena->id == auxArestas->destinoID) {
					auxArestas->destino = aux2antena;		// Liga a Aresta ao seu destino
					//printf("Ligado aresta com destino ID %d\n", auxArestas->destino->id);  //debug
					break;
				}
				aux2antena = aux2antena->proxAntena;
			}
			auxArestas = auxArestas->proxAresta;
		}
		auxAntena = auxAntena->proxAntena;
	}

	return antenaHead;
}


/**
 * @brief Função para Remover uma Antena e as respetivas Arestas do grafo.
 *
 * @param antenaHead Apontador para o início do grafo.
 * @param antenaID Identificador da Antena a ser removida.
 * @param val Controlo de erros.
 *
 * @return Apontador para o início do grafo atualizado.
 */
Antena* RemoverAntena(Antena* antenaHead, int antenaID, int* val) {

	// Testes para validação dos parâmetros
	if (antenaHead == NULL) {
		*val = -2;
		return antenaHead;
	}

	if (antenaID < 0) {
		*val = -6;
		return antenaHead;
	}

	Antena* frenteAntena = antenaHead;
	Antena* trasAntena = frenteAntena;
	Arestas* trasAresta = frenteAntena->arestas;

	// Enquanto houver antenas
	while (frenteAntena != NULL) {

		Arestas* frenteAresta = frenteAntena->arestas;

		// Se for a Antena a ser removida
		if (frenteAntena->id == antenaID) {

			// Se for a primeira Antena da lista
			if (antenaHead == frenteAntena) {

				// Elimina as arestas primeiro
				while (frenteAresta != NULL) {
					trasAresta = frenteAresta;
					frenteAresta = frenteAresta->proxAresta;
					free(trasAresta);
				}

				trasAntena = antenaHead;
				frenteAntena = frenteAntena->proxAntena;
				antenaHead = frenteAntena;
				free(trasAntena);
			}

			// Se não for a primeira Antena da lista
			else {
				trasAntena = antenaHead;
				frenteAresta = frenteAntena->arestas;

				// Enquanto houver arestas, elimina
				while (frenteAresta != NULL) {
					trasAresta = frenteAresta;
					frenteAresta = frenteAresta->proxAresta;
					free(trasAresta);
				}
				trasAntena->proxAntena = frenteAntena->proxAntena;
				trasAntena = frenteAntena;
				frenteAntena = frenteAntena->proxAntena;
				free(trasAntena);
			}
		}

		// Se não for a primeira Antena a ser removida, procura as Arestas correspondentes à Antena a ser removida 
		frenteAresta = frenteAntena->arestas;

		// Enquanto houver Arestas
		while (frenteAresta != NULL) {

			// Se tiver uma Aresta da Antena a ser removida
			if (frenteAresta->destinoID == antenaID) {

				// Se for a primeira Aresta
				if (frenteAntena->arestas->destinoID == antenaID) {
					trasAresta = frenteAresta;
					frenteAresta = frenteAresta->proxAresta;
					frenteAntena->arestas = frenteAresta;
					free(trasAresta);
					break;
				}

				// Se não for a primeira Aresta
				else {
					trasAresta->proxAresta = frenteAresta->proxAresta;
					trasAresta = frenteAresta;
					frenteAresta = frenteAresta->proxAresta;
					free(trasAresta);
					break;
				}

				//trasAresta = frenteAresta;
				//frenteAresta = frenteAresta->proxAresta;
			}

			trasAresta = frenteAresta;
			frenteAresta = frenteAresta->proxAresta;
		}

		frenteAntena = frenteAntena->proxAntena;
	}

	*val = 0;
	return antenaHead;
}

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
Antena* LerFicheiro(char* nomeFicheiro, Antena* antenaHead, int* id, int* val) {

	*val = 0;
	
	Antena* aux = NULL;
	FILE* fp;
	
	// Abre o ficheiro no modo leitura
	if (fopen_s(&fp, nomeFicheiro, "r") != 0) {
		*val = -4;
		return NULL;
	}

	char linhaFicheiro[256];
	int numeroLinha = 0, numeroColuna = 0;

	// Lê as linhas
	while (fgets(linhaFicheiro, sizeof(linhaFicheiro), fp)) {

		numeroColuna = 0;  // Reset ao numero de coluna quando muda de linha

		// Percorre a linha
		while ((linhaFicheiro[numeroColuna] != '\n') && (linhaFicheiro[numeroColuna] != '\0')) {
			if (linhaFicheiro[numeroColuna] != '.') {
				aux = CriarAntena(numeroLinha, numeroColuna, linhaFicheiro[numeroColuna], id, val);
				antenaHead = InserirAntena(antenaHead, aux, val);
			}
			numeroColuna++;
		}
		numeroLinha++;
	}
	fclose(fp);

	return antenaHead;
}


/**
 * @brief Função que permite gravar apenas a posição das Antenas num ficheiro não binário.
 * 
 * @param nomeFicheiro Nome do ficheiro onde se pretende guardar a posição das Antenas.
 * @param antenaHead Apontador para o início da lista das Antenas.
 * 
 * @return 0 em caso de sucesso
 */
int GravarFicheiro(char* nomeFicheiro, Antena* antenaHead) {

	if (antenaHead == NULL) {
		return -2;
	}

	Antena* aux = antenaHead;
	Antena* aux2 = antenaHead;
	int numeroLinhas = 0;
	int numeroColunas = 0;

	// Medir o tamanho da matriz
	while (aux != NULL) {
		if (numeroLinhas < aux->linha) 
			numeroLinhas = aux->linha;
		if (numeroColunas < aux->coluna) 
			numeroColunas = aux->coluna;
		aux = aux->proxAntena;
	}

	FILE* fp;

	// Abrir o ficheiro em modo escrita
	if (fopen_s(&fp, nomeFicheiro, "w") != 0) {
		return -4;
	}

	// Preenche as linhas
	for (int i = 0; i <= numeroLinhas; i++) {

		// Preenche as colunas
		for (int j = 0; j <= numeroColunas; j++) {

			// Quando as coordenadas forem achadas
			if (aux2 != NULL && (aux2->linha == i && aux2->coluna == j)) {
				fprintf(fp, "%c", aux2->tipoAntena);
				aux2 = aux2->proxAntena;
			}

			else {
				fprintf(fp, "%c", '.');
			}
		}

		fprintf(fp, "%c", '\n');
	}

	fclose(fp);
	return 0;
}


/**
 * @brief Função para gravar os dados do grafo em ficheiro binário.
 * 
 * @param nomeFicheiro Nome do ficheiro onde se pretende guarda a informação do grafo.
 * @param antenaHead Apontador para o início do grafo.
 * @param id Variável que contém quantas Antenas o grafo tem.
 * 
 * @return 0 em caso de sucesso.
 */
int GravarFicheiroBinario(char* nomeFicheiro, Antena* antenaHead, int id) {

	// Testes para validação dos parâmetros
	if (antenaHead == NULL)
		return -2;
	
	Antena* auxAntenas = antenaHead;
	AntenaFile auxAntenaFile;
	ArestasFile auxArestaFile;

	FILE* fp;

	// Abre o ficheiro binário para escrita
	if (fopen_s(&fp, nomeFicheiro, "wb") != 0)
		return -4;

	// Escreve um int que contem o numero de Antenas a guardar
	fwrite(&id, sizeof(int), 1, fp);

	// Ciclo para guardar a informação
	for (int i = 0; i < id; i++) {

		auxAntenaFile.id = auxAntenas->id;
		auxAntenaFile.linha = auxAntenas->linha;
		auxAntenaFile.coluna = auxAntenas->coluna;				// Passar a informação para uma struct auxiliar sem apontadores
		auxAntenaFile.tipoAntena = auxAntenas->tipoAntena;
		auxAntenaFile.visitado = auxAntenas->visitado;

		// Escreve uma antena
		fwrite(&auxAntenaFile, sizeof(AntenaFile), 1, fp);
		
		Arestas* auxArestas = auxAntenas->arestas;

		// Enquanto existir arestas na Antena
		while (auxArestas != NULL) {
			auxArestaFile.distancia = auxArestas->distancia;		// Passar a informação para uma struct auxiliar sem apontadores
			auxArestaFile.destinoID = auxArestas->destinoID;

			// Escrever uma aresta
			fwrite(&auxArestaFile, sizeof(ArestasFile), 1, fp);

			auxArestas = auxArestas->proxAresta;
		}

		// Escrita de um tipo de aresta com dados impossíveis para saber quando terminou as arestas daquela Antena.
		auxArestaFile.distancia = -1;					
		fwrite(&auxArestaFile, sizeof(ArestasFile), 1, fp);

		auxAntenas = auxAntenas->proxAntena;
	}
	
	fclose(fp);
	
	return 0;
}


/**
 * @brief Função para ler a informação do Grafo contida num ficheiro binário.
 * 
 * @param nomeFicheiro Nome do ficheiro que contem a informação do grafo.
 * @param id Apontador para a variável que contem a identificação da Antena.
 * @param val Controlo de erros.
 * 
 * @return Apontador para o início do grafo.
 */
Antena* LerFicheiroBinario(char* nomeFicheiro, int* id, int* val) {

	*val = 0;
    int totalid = 0;
    Antena* headTemp = NULL;
    Antena* auxAntena = NULL;
    Arestas* auxArestas = NULL;
    Arestas* aux2arestas = NULL;
    AntenaFile auxAntenaFile;
    ArestasFile auxArestaFile;
    FILE* fp;

	// Abrir o ficheiro binário em modo leitura
    if (fopen_s(&fp, nomeFicheiro, "rb") != 0) {
        *val = -4;
        return NULL;
    }

    fread(&totalid, sizeof(int), 1, fp);  // Lê o numero total de antenas

    for (int i = 0; i < totalid; i++) {
        fread(&auxAntenaFile, sizeof(AntenaFile), 1, fp);  // Lê uma antena

        int idTemp = auxAntenaFile.id;  // Lê o ID da antena do arquivo
        auxAntena = CriarAntena(auxAntenaFile.linha, auxAntenaFile.coluna, auxAntenaFile.tipoAntena, &idTemp, val);
		(*id)++;

        if (*val != 0) {
            fclose(fp);
            return NULL;
        }

		// Inserir a Antena na lista
        headTemp = InserirAntena(headTemp, auxAntena, val);

        int primeiraaresta = 1;
        aux2arestas = NULL;

        // Lê as arestas
        while (1) {

			// Lê as arestas
            fread(&auxArestaFile, sizeof(ArestasFile), 1, fp);

            if (auxArestaFile.distancia == -1)  // Marca o final das arestas
                break;

            auxArestas = CriarAresta(auxAntena, auxArestaFile.destinoID, auxArestaFile.distancia, val);

			// Se for a primeira aresta, ligar a antena à mesma
            if (primeiraaresta == 1) {
                aux2arestas = auxArestas;
                auxAntena->arestas = auxArestas;
                primeiraaresta = 0;
            } 

			// Se não for a primeira, liga na última posição
			else {
                aux2arestas->proxAresta = auxArestas;
                aux2arestas = aux2arestas->proxAresta;
            }
        }
    }

    fclose(fp);
    headTemp = LigarAntenaDestinoAntenaId(headTemp, val);
    return headTemp;
}

#pragma endregion


#pragma region FUNÇÕES TESTE

// ----------------------------------------------------------------------------------
//									FUN��ES TESTE
// ----------------------------------------------------------------------------------


/*int mostrarLista(Antena* head) {

	Antena* aux = head;

	if (aux == NULL)
		return 0;

	while (aux) {
		printf("%c", aux->tipoAntena);
		aux = aux->proxAntena;
	}

	return 1;
}*/

int mostrarLista(Antena* head) {
	Antena* atual = head;
	while (atual != NULL) {
		printf("Antena ID: %d (%d,%d) Tipo: %c\n", atual->id, atual->linha, atual->coluna, atual->tipoAntena);
		Arestas* aresta = atual->arestas;
		while (aresta != NULL) {
			if (aresta->destinoID >= 0)
				printf("  -> Aresta para Antena ID: %d (Distancia: %d)\n", aresta->destinoID, aresta->distancia);
			else
				printf("  -> Aresta para ID desconhecido: %d (Distancia: %d)\n", aresta->destinoID, aresta->distancia);
			aresta = aresta->proxAresta;
		}
		atual = atual->proxAntena;
	}
	return 0;
}

int mostrarListaArestas(Arestas* head) {

	Arestas* aux = head;

	if (aux == NULL)
		return 0;

	while (aux) {
		printf("Distancia: %d || Linha: %d || Coluna: %d\n", aux->distancia, aux->origem->linha, aux->origem->coluna);
		aux = aux->proxAresta;
	}

	return 1;
}


int ContarAntenas(Antena* head) {
	int count = 0;
	while (head != NULL) {
		count++;
		head = head->proxAntena;
	}
	return count;
}

#pragma endregion