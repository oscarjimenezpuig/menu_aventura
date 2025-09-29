/*
============================================================
  Fichero: objeto.h
  Creado: 25-09-2025
  Ultima Modificacion: lun 29 sep 2025 11:59:00
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef OBJETO_H
#define OBJETO_H

#include "mapa.h"

#define TESORO 1
#define ARMA 2
#define LLAVE 3
#define MAPA 4

#define ATAQUE 1
#define DEFENSA 2

#define NADA 0
#define SALIDA 1
#define TIENDA 2

#define OBJETOS 200

typedef signed short i2;

typedef struct {
	u2 nombre;
	u1 tipo;
	u2 x,y;
	union {
		u2 valor; //tesoro
		struct { //arma
			u1 subtipo;
			u1 plus;
			u1 duracion;
		}; 
		u1 lugar; //llave
	};
} Objeto;

extern u1 objetos;
extern Objeto objeto[OBJETOS];

Objeto* obj_new(u2 id_nombre);
//define un nuevo objeto

void obj_pur(Objeto* o);
//envia el objeto al purgatorio

void obj_rnd_pos(Objeto* o);
//da posicion aleatoria en el mapa

void obj_prt(Objeto* o);
//imprime y describe un objeto

void obj_def();
//define todos los objetos
		

#endif //OBJETO_H

