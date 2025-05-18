/*****************************************************************//**
 * @file   antena.h
 * @brief  Ficheiro com a declaração das structs utilizadas nas listas.
 * 
 * @author ptnunooliveira
 * @date   March 2025
 *********************************************************************/

#pragma once

typedef struct Antena {
	int linha;
	int coluna;
	char tipoantena;
	struct Antena* Next;
} Antena;

typedef struct AntenaFile {
	int linha;
	int coluna;
	char tipoantena;
} AntenaFile;
