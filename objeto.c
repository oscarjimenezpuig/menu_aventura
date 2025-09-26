/*
============================================================
  Fichero: objeto.c
  Creado: 25-09-2025
  Ultima Modificacion: vie 26 sep 2025 12:12:06
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

void obj_pur(Objeto* o) {
	o->x=MAPW;
	o->y=MAPH;
}

void obj_rnd_pos(Objeto* o) {
	o->x=rand()%MAPW;
	o->y=rand()%MAPH;
}

void obj_prt(Objeto* o) {
	printf("%s, ",o->nombre);
	if(o->tipo==ARMA) {
		printf(" es un arma de %s",(o->subtipo==ATAQUE)?"ataque":"defensa");
		printf("(+%i).",o->plus);
	} else {
		printf(" es un cofre que contiene %i monedas de oro.",o->valor);
	}
};
