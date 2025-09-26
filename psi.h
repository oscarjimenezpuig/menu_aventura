/*
============================================================
  Fichero: psi.h
  Creado: 25-09-2025
  Ultima Modificacion: dijous, 25 de setembre de 2025, 20:48:06
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
	i2 x,y;
	u1 equipo;
	u1 fuerza;
	u1 agilidad;
	u1 capacidad;
	u1 vida;
	u1 contenidos;
	Objeto* contenido[MAXPUN];
} Psi;

extern Psi psi[PSIS];
extern u2 psis;

Psi* psi_new(char* nombre);

u1 psi_ins_obj(Psi* psi,Objeto* obj);

void psi_rnd_pos(Psi* psi);

u1 psi_mov(Psi* p,u1 dir);

#endif //PSI_H
