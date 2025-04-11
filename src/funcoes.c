/*****************************************************************//**
 * @file   funcoes.c
 * @brief  Implementação de funções para manipulação de listas ligadas.
 *			
 * 
 * @author ptnunooliveira
 * @date   March 2025
 *********************************************************************/

#include "antena.h"
#include "funcoes.h"

/**
 * @brief Função para ler um ficheiro binário e carregar os dados numa lista ligada.
 * 
 * @param NomeFicheiro Nome do ficheiro a ler.
 * @param head Apontador para o início da lista.
 * 
 * @return true se o ficheiro foi aberto com sucesso, false caso contrário.
 */
bool LerListasBinario(const char* NomeFicheiro, Antena** head) {

	FILE* fp;
	if (fopen_s(&fp, NomeFicheiro, "rb") != 0)
		return false;

	AntenaFile auxFILE;
	Antena* aux;

	// Lê o ficheiro binário e insere os elementos na lista
	while (fread(&auxFILE, sizeof(AntenaFile), 1, fp)) {
		aux = CriarAntena(auxFILE.linha, auxFILE.coluna, auxFILE.tipoantena);
		*head = InserirAntena(*head, aux);
	}

	fclose(fp);

	return true;
}


/**
 * @brief Função para guardar uma lista ligada num ficheiro binário.
 * 
 * @param NomeFicheiro Nome do ficheiro a guardar a lista.
 * @param head Apontador para o início da lista a ser guardada.
 * 
 * @return true se guardado com sucesso, false caso contrário.
 */
bool GuardarListasBinario(const char* NomeFicheiro, Antena* head) {

	if (head == NULL)
		return false;

	FILE* fp;
	if (fopen_s(&fp, NomeFicheiro, "wb") != 0)			// Verifica se o ficheiro foi aberto com sucesso
		return false;
	
	Antena* aux = head;
	AntenaFile auxFILE;

	// Percorre a lista e escreve os dados no ficheiro
	while (aux != NULL) {
		auxFILE.linha = aux->linha;
		auxFILE.coluna = aux->coluna;
		auxFILE.tipoantena = aux->tipoantena;
		
		fwrite(&auxFILE, sizeof(AntenaFile), 1, fp);
		
		aux = aux->Next;
	}

	fclose(fp);
	return true;
}


/**
 * @brief Função que lê o ficheiro .txt e cria lista ligada com as Antenas.
 *
 * @param NomeFicheiro Nome do ficheiro a ler.
 * @param head Apontador o início da lista das Antenas.
 *
 * @return true se foi aberto com sucesso, false caso contrário.
 */
bool LerFicheiro(const char* NomeFicheiro, Antena** head) {
	
	Antena* aux = NULL;				
	FILE* fp;
	if (fopen_s(&fp, NomeFicheiro, "r") != 0)			
		return false;

	char linhaFicheiro[256];							
	int numerolinha = 0, numerocoluna = 0;

	// Lê cada linha do ficheiro e cria antenas conforme os caracteres encontrados
	while (fgets(linhaFicheiro, sizeof(linhaFicheiro), fp)) {											// Lê uma linha do ficheiro de cada vez
		while ((linhaFicheiro[numerocoluna] != '\n') && linhaFicheiro[numerocoluna] != '\0') {			// Lê um caractere da linha de cada vez
			if ((linhaFicheiro[numerocoluna] != '.') && (linhaFicheiro[numerocoluna] != '#')) {			// Se for uma Antena
				aux = CriarAntena(numerolinha, numerocoluna, linhaFicheiro[numerocoluna]);
				*head = InserirAntena(*head, aux);
			}
			numerocoluna++;
		}
		numerocoluna = 0;			// Reseta o número de coluna
		numerolinha++;			// Próxima linha
	}
	fclose(fp);

	return true;
}  


/**
 * @brief Função para gravar a matriz alterada num ficheiro de texto.
 *
 * @param NomeFicheiro Nome do ficheiro onde será guardada a informação.
 * @param head Apontador para o início da lista das antenas.
 *
 * @return true se gravou com sucesso, false caso contrário.
 */
bool GravarFicheiro(const char* NomeFicheiro, Antena* head, Antena* headnefasto) {

	if (head == NULL) return false;

	
	Antena* aux = head;
	Antena* aux2 = head;
	int nlinhasmatriz = aux->linha, ncolunasmatriz = aux->coluna;			// Dimensões da matriz
	int nlinhasMin = aux->linha, ncolunasMin = aux->coluna;					// Mínimos da a matriz

	FILE* fp;
	if (fopen_s(&fp, NomeFicheiro, "w") != 0)	
		return false;

	// Determina os limites da matriz baseada nas coordenadas das antenas
	while (aux != NULL) {							
		if (aux->coluna > ncolunasmatriz)			
			ncolunasmatriz = aux->coluna;
		if (aux->linha > nlinhasmatriz)
			nlinhasmatriz = aux->linha;
		if (aux->linha < nlinhasMin)
			nlinhasMin = aux->linha;
		if (aux->coluna < ncolunasMin)
			ncolunasMin = aux->coluna;
		aux = aux->Next;
		
	}

	// Ciclo para criar as linhas. Inicia com o menor número até chegar ao maior número.
	for (int i = nlinhasMin; i <= nlinhasmatriz; i++) {			

		// Ciclo para criar as colunas. Inicia com o menor número até chegar ao maior número.
		for (int j = ncolunasMin; j <= ncolunasmatriz; j++) {
			if ((aux2 != NULL) && (i == aux2->linha) && (j == aux2->coluna)) {
				fprintf(fp, "%c", aux2->tipoantena);
				aux2 = aux2->Next;
				continue;
			}
			fprintf(fp,"%c",'.');
		}
		fprintf(fp,"%c",'\n');
	}
	return true;
}


/**
 * @brief Função para criar uma Antena.
 * 
 * @param linha Coordenada da linha da Antena.
 * @param coluna Coordenada da coluna da Antena.
 * @param tipoantena Tipo de Antena.
 * 
 * @return Apontador para a nova Antena.
 */
Antena* CriarAntena(int linha, int coluna, char tipoantena) {                   

	// Aloca memória do tamanho Antena
	Antena* aux = malloc(sizeof(Antena));				

	if (aux == NULL)								
		return NULL;  

	// Dá valores para os vários campos do tipo Antena
	aux->linha = linha;                 
	aux->coluna = coluna;
	aux->tipoantena = tipoantena;
	aux->Next = NULL;								

	return aux;								
}


/**
 * @brief Função para mostrar a matriz no terminal.
 *
 * @param head Apontador para o início da lista das Antenas.
 * @param headnefasto Apontador para o início da lista das zonas Nefastas.
 *
 * @return 1 com sucesso, 0 caso contrário.
 */
bool MostrarMatriz(Antena* head, Antena* headnefasto) {

	if (head == NULL) return false;			// Se não houver Antenas

	Antena* aux = head;
	Antena* aux2 = head;
	Antena* nef = headnefasto;
	Antena* nef2 = headnefasto;
	int nlinhasmatriz = aux->linha, ncolunasmatriz = aux->coluna;			
	int ncolunasNEF = aux->coluna, nlinhasNEF = aux->linha;				

	// Determina os limites máximos da matriz baseada nas coordenadas das antenas
	while (aux != NULL) {							
		if (aux->coluna > ncolunasmatriz)			
			ncolunasmatriz = aux->coluna;
		if (aux->linha > nlinhasmatriz)
			nlinhasmatriz = aux->linha;
		aux = aux->Next;
	}

	// Determina os limites máximos e mínimos da matriz baseada nas coordenadas das zonas nefastas
	while (nef != NULL) {							
		if (nef->coluna > ncolunasmatriz)	
			ncolunasmatriz = nef->coluna;
		if (nef->coluna < ncolunasNEF)
			ncolunasNEF = nef->coluna;
		if (nef->linha > nlinhasmatriz)
			nlinhasmatriz = nef->linha;
		if (nef->linha < nlinhasNEF)
			nlinhasNEF = nef->linha;
		nef = nef->Next;
	}
	
	// Ciclo para criar as linhas. Inicia com o menor número até chegar ao maior número.
	for (int i = nlinhasNEF; i <= nlinhasmatriz; i++) {

		// Ciclo para criar as colunas. Inicia com o menor número até chegar ao maior número.
		for (int j = ncolunasNEF; j <= ncolunasmatriz; j++) {
			if (aux2 != NULL && i == aux2->linha && j == aux2->coluna) {
				printf("%c", aux2->tipoantena);
				aux2 = aux2->Next;

				// Se uma Antena e Nefasta tiverem as mesmas coordenadas, dar prioridade à impressão da Antena
				if (nef2 != NULL && i == nef2->linha && j == nef2->coluna) {
					nef2 = nef2->Next;
				}

				continue;
			}
			else if ((nef2 != NULL) && (i == nef2->linha) && (j == nef2->coluna)) {
				printf("%c", nef2->tipoantena);
				nef2 = nef2->Next;
				continue;
			}
			putchar('.');
		}
		putchar('\n');
	}

	return true;
}             


/**
 * @brief Função para inserir de forma ordenada uma Antena na lista ligada.
 * 
 * @param head	Apontador para o início da lista das Antenas.
 * @param nova	Apontador para a nova Antena a introduzir.
 * 
 * @return Apontador para o início da lista das Antenas.
 */
Antena* InserirAntena(Antena* head, Antena* nova) {

	if (nova == NULL)	return head;			// Se verdadeiro, não acontece nada

	if (head == NULL) {							// Se verdadeiro, nova é o início da lista
		head = nova;
		nova->Next = NULL;
		return head;
	}
	
	if (nova->linha < head->linha) {			// Se verdadeiro, nova é menor que o primeiro da lista                         
		nova->Next = head;						// nova passa a ser o head da lista
		head = nova;
		return head;
	}

	if (nova->linha == head->linha) {				// Se verdadeiro, vai comparar a coluna
		if (nova->coluna < head->coluna) {			// Se verdadeiro, nova é menor que o primeiro da lista
			nova->Next = head;						// nova passa a ser o head da lista
			head = nova;
			return head;
		}
	}

	// Caso não aconteça nenhuma das possibilidades anteriores:

	// Criação de variáveis para percorrer a lista
	Antena* frente = head;
	Antena* tras = frente;

	while (nova->linha > frente->linha) {			
		if (frente->Next == NULL) {
			frente->Next = nova;
			nova->Next = NULL;
			return head;
		}
		tras = frente;
		frente = frente->Next;
	}



	if (nova->linha == frente->linha) {
		while ((nova->linha == frente->linha) && (nova->coluna > frente->coluna)) {
			if (frente->Next == NULL) {
				frente->Next = nova;
				nova->Next = NULL;
				return head;
			}
			tras = frente;
			frente = frente->Next;
		}
		if (nova->coluna == frente->coluna) {
			free(nova);
			return head;
		}
	}
	nova->Next = frente;
	tras->Next = nova;
	return head;
}


/**
 * @brief Função para criar a lista de zonas nefastas com base nas antenas existentes.
 *
 * @param head Apontador para o início da lista das Antenas.
 * 
 * @return Apontador para o início da lista das zonas Nefastas.
 */
Antena* CriarZonasNefastas(Antena* head) {

	Antena* aux = head;
	Antena* aux2 = aux;
	Antena* headnefasto = NULL;
	/*int ncolunasmatriz = 0, nlinhasmatriz = 0;

	
	while (aux != NULL) {
		if (aux->linha > nlinhasmatriz)
			nlinhasmatriz = aux->linha;
		if (aux->coluna > ncolunasmatriz)
			ncolunasmatriz = aux->coluna;
		aux = aux->Next;
	}

	aux = head;
	*/


	while (aux != NULL) {
		while (aux2 != NULL) {

			if (aux == aux2) {
				aux2 = aux2->Next;
				continue;
			}

			// Se ambas as Antenas forem do mesmo tipo, cria uma zona Nefasta
			if (aux->tipoantena == aux2->tipoantena) {
				Antena* novo = (Antena*)malloc(sizeof(Antena));
				if (novo == NULL) return 0;

				// Algoritmo para descoberta das coordenadas das zonas Nefastas
				novo->Next = NULL;
				novo->linha = aux->linha + (aux->linha - aux2->linha);
				novo->coluna = aux->coluna + (aux->coluna - aux2->coluna);
				novo->tipoantena = '#';

				// Verifica se já existe uma zona Nefasta naquelas coordenadas
				Antena* tmp = headnefasto;
				int repetido = 0;
				while (tmp != NULL) {
					if (tmp->linha == novo->linha && tmp->coluna == novo->coluna) {
						repetido = 1;
						break;
					}
					tmp = tmp->Next;
				}

				if (repetido == 0)
					headnefasto = InserirAntena(headnefasto, novo);
				else if (repetido == 1)
					free(novo);
			}
			aux2 = aux2->Next;
		}
		aux2 = head;
		aux = aux->Next;
	}
	return headnefasto;
}


/**
 * @brief Função para remover uma antena da lista ligada.
 * 
 * @param head Apontador para o início da lista.
 * @param linha linha da Antena a ser removida.
 * @param coluna coluna da Antena a ser removida.
 * 
 * @return true se a Antena foi removida, false caso contrário.
 */
bool RemoverAntena(Antena** head, int linha, int coluna) {

	if (*head == NULL)
		return false;

	Antena* frente = *head;
	Antena* tras = NULL;

	if (frente->linha == linha && frente->coluna == coluna) {
		*head = frente->Next;
		free(frente);
		return true;
	}

	while (frente != NULL) {
		if (frente->linha == linha && frente->coluna == coluna) {
			tras->Next = frente->Next;
			free(frente);
			return true;
		}
		tras = frente;
		frente = frente->Next;
	}
	return false;
}









// -------------------------------------------------------------------------------------------------- // 


// FUNÇÕES TESTE

int mostrarLista(Antena* head) {

	Antena* aux = head;

	if (aux == NULL)
		return 0;

	while (aux) {
		printf("%c", aux->tipoantena);
		aux = aux->Next;
	}

	return 1;
}


int mostrarListaNEFASTOS(Antena* headnefasto) {

	Antena* aux = headnefasto;

	if (aux == NULL)
		return 0;

	while (aux) {
		printf("%c", aux->tipoantena);
		aux = aux->Next;
	}

	return 1;
}



void ImprimirConteudoBinario(const char* NomeFicheiro) {
	FILE* fp;

	if (fopen_s(&fp, NomeFicheiro, "rb") != 0) {
		printf("Erro ao abrir o ficheiroteste.\n");
		return; 
	}

	int i = 1;
	AntenaFile aux;
	while (fread(&aux, sizeof(AntenaFile), 1, fp)) {
		printf("Antena %d: linha = %d, coluna = %d, Tipo = %c\n", i, aux.linha, aux.coluna, aux.tipoantena);
		i++;
	}

	fclose(fp);
}