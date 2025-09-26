/*
============================================================
  Fichero: objeto.h
  Creado: 25-09-2025
  Ultima Modificacion: vie 26 sep 2025 12:16:03
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef OBJETO_H
#define OBJETO_H

#include <string.h>

#include "mapa.h"

#define TESORO 1
#define ARMA 2

#define ATAQUE 1
#define DEFENSA 1

#define OBJETOS 100

#define NOMLEN 32

typedef signed short i2;

typedef struct {
	char nombre[NOMLEN];
	u1 tipo;
	u2 x,y;
	union {
		u2 valor;
		struct {
			u1 subtipo;
			u1 plus;
		};
	};
} Objeto;

extern u1 objetos;
extern Objeto objeto[OBJETOS];

Objeto* obj_new(char* nombre);
//define un nuevo objeto

void obj_pur(Objeto* o);
//envia el objeto al purgatorio

void obj_rnd_pos(Objeto* o);
//da posicion aleatoria en el mapa

void obj_prt(Objeto* o);
//imprime y describe un objeto
		

#endif //OBJETO_H

