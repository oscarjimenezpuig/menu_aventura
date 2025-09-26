/*
============================================================
  Fichero: objeto.c
  Creado: 25-09-2025
  Ultima Modificacion: dijous, 25 de setembre de 2025, 20:48:31
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "objeto.h"

u1 objetos=0;
Objeto objeto[OBJETOS];

Objeto* obj_new(char* nombre) {
	if(objetos<OBJETOS) {
		Objeto* o=objeto+objetos;
		objetos++;
		strcpy(o->nombre,nombre);
		return o;
	}
	return NULL;
}

void obj_rnd_pos(Objeto* o) {
	o->x=rand()%MAPW;
	o->y=rand()%MAPH;
}
