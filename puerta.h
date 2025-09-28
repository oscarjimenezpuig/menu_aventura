/*
============================================================
  Fichero: puerta.h
  Creado: 28-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 07:07:36
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef PUERTA_H
#define PUERTA_H

#include "psi.h"

#define PUERTAS 2

typedef struct {
	u2 nombre;
	u1 tipo;
	u1 abierta;
	u2 x,y;
} Puerta;

extern Puerta puerta[PUERTAS];

void puer_ini();
//inicia las puertas

void puer_sal();
//se utiliza la puerta de salida

void puer_tie();
//se utiliza la tienda

void puer_prt(Puerta* p);
//imprime la puerta

#endif //PUERTA_H
