/*
============================================================
  Fichero: objeto.c
  Creado: 25-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 08:58:24
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "objeto.h"

u1 objetos=0;
Objeto objeto[OBJETOS];

Objeto* obj_new(char* nombre) {
	if(objetos<OBJETOS) {
		Objeto* o=objeto+objetos;
		nom_new(nombre,&(o->nombre));
		objetos++;
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
	printf("%s",nombre[o->nombre]);
	if(o->tipo==ARMA) {
		printf(", es un arma de %s (+%i) con duracion %i.",(o->subtipo==ATAQUE)?"ataque":"defensa",o->plus,o->duracion);
	} else if(o->tipo==TESORO) {
		printf(", es un cofre que contiene %i monedas de oro.",o->valor);
	}
};

void llav_ini() {
	Nombre nllave[]={"Llave de oro","Llave de plata","Llave de cobre"};
	u1 usado[]={0,0,0};
	for(u1 k=0;k<3;k++) {
		Objeto* o=obj_new(nllave[k]);
		if(o) {
			o->tipo=LLAVE;
			u1 lugar;
			do {
				lugar=rand()%3;
			}while(usado[lugar]==1);
			usado[lugar]=1;
			o->lugar=lugar;
			obj_rnd_pos(o);
		};
	}
}

void pla_ini() {
	Objeto* o=obj_new("Plano");
	o->tipo=MAPA;
	obj_rnd_pos(o);
};


