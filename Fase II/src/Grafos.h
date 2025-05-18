/*****************************************************************//**
 * @file   Grafos.h
 * @brief  Ficheiro que contem as structs usadas.
 * 
 * @author ptnunooliveira
 * @date   May 2025
 *********************************************************************/

#pragma once

typedef struct Antena {
	int id;
	int linha;
	int coluna;
	char tipoAntena;			
	int visitado;					// Se foi visitado
	struct Antena* proxAntena;		// Lista de Antenas
	struct Arestas* arestas;		// Lista das Arestas daquela Antena
} Antena;

typedef struct Arestas {
	int distancia;
	int destinoID;
	struct Antena* origem;			// Antena origem da Aresta
	struct Antena* destino;			// Antena destino da Aresta
	struct Arestas* proxAresta;		// Lista de Arestas
} Arestas;

typedef struct AntenaFile {
	int id;
	int linha;
	int coluna;
	char tipoAntena;
	int visitado;
} AntenaFile;

typedef struct ArestasFile {
	int distancia;
	int destinoID;
} ArestasFile;
