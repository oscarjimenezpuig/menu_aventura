/*
============================================================
  Fichero: psi.h
  Creado: 25-09-2025
  Ultima Modificacion: vie 26 sep 2025 12:16:03
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef PSI_H
#define PSI_H

#include "objeto.h"

#define PSIS 100
#define MAXPUN 10

typedef signed char i1;

typedef struct {
	char nombre[NOMLEN];
	u2 x,y;
	u1 equipo;
	u1 fuerza;
	u1 agilidad;
	u1 capacidad;
	u1 oro;
	u1 vida;
	u1 contenidos;
	Objeto* contenido[MAXPUN];
} Psi;

extern Psi psi[PSIS];
extern u2 psis;

Psi* psi_new(char* nombre);

u1 psi_ins_obj(Psi* psi,Objeto* obj);
//insertar objeto (independientemente de donde este) no ha de superar capacidad de psi

u1 psi_cog_obj(Psi* psi,Objeto* obj);
//coger objeto, es como insertar pero el objeto ha de estar en la posicion del psi

void psi_pur(Psi* p);
//envia al psi al purgatorio

void psi_rnd_pos(Psi* psi);

u1 psi_mov(Psi* p,u1 dir);

#endif //PSI_H
