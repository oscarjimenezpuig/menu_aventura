/*
============================================================
  Fichero: enemigo.c
  Creado: 27-09-2025
  Ultima Modificacion: dissabte, 27 de setembre de 2025, 12:51:29
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "enemigo.h"

Psi* ene_new(char* n,u1 vida) {
	Psi* p=NULL;
	if(vida) {
		p=psi_new(n);
		if(p) p->vida=vida;
	}
	return p;
}

static u1 paseo(Psi* p) {
	u1 sal=map[p->x][p->y];
	u1 dir=0;
	while(!dir) {
		u1 ndir=rand()%4;
		dir=NORTE<<ndir;
		dir=(dir & sal)?dir:0;
	}
	return psi_mov(p,dir);
}

static u1 coger(Psi* p) {
	if(p->contenidos<p->capacidad-1) {
		Objeto* op[objetos];
		u1 ops=0;
		for(u1 n=0;n<objetos;n++) {
			Objeto* oe=objeto+n;
			if(oe->x==p->x && oe->y==p->y) {
				op[ops++]=oe;
			}
		}
		if(ops) {
			u1 noac=rand()%ops;
			return psi_cog_obj(p,op[noac]);
		}
	}
	return 0;
}

u1 ene_act(Psi* p) {
	if(psi_is_alv(p)) {
		if(!coger(p)) paseo(p);
		return 1;
	}
	return 0;
}

u1 enes_act() {
	u1 ret=0;
	for(u1 k=0;k<psis;k++) {
		Psi* p=psi+k;
		if(p->jugador==0) {
			ret|=ene_act(p);
		}
	}
	return ret;
}
			

u1 ene_enc(Psi* p) {
	u1 ataque=p->fuerza>protagonista->fuerza || (p->fuerza==protagonista->fuerza && p->habilidad<protagonista->habilidad);
	if(!ataque && protagonista->habilidad>p->habilidad) ataque=rand()%2;
	Psi* ap[]={protagonista};
	return (ataque)?psi_atak(p,protagonista):psi_huir(p,1,ap);
}


