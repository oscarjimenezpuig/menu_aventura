/*
============================================================
  Fichero: psi.c
  Creado: 25-09-2025
  Ultima Modificacion: dijous, 25 de setembre de 2025, 20:44:48
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "psi.h"

Psi psi[PSIS];
u2 psis=0;

Psi* psi_new(char* n) {
	if(psis<PSIS) {
		Psi* p=psi+psis;
		psis++;
		strcpy(p->nombre,n);
		psi->contenidos=0;
		return p;
	}
	return NULL;
}

u1 psi_ins_obj(Psi* p,Objeto* o) {
	if(o->x==p->x && o->y==p->y && p->contenidos<p->capacidad) {
		o->x=o->y=-1;
		p->contenido[p->contenidos++]=o;
		return 1;
	}
	return 0;
}

void psi_rnd_pos(Psi* p) {
	p->x=rand()%MAPW;
	p->y=rand()%MAPH;
}

u1 psi_mov(Psi* p,u1 d) {
	u1 salidas=map[p->x][p->y];
	if(d & salidas) {
		switch(d) {
			case NORTE:
				p->y--;
				break;
			case SUR:
				p->y++;
				break;
			case ESTE:
				p->x++;
				break;
			case OESTE:
				p->x--;
				break;
		}
		return 1;
	}
	return 0;
}


	
