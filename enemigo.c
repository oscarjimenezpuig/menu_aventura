/*
============================================================
  Fichero: enemigo.c
  Creado: 27-09-2025
  Ultima Modificacion: dilluns, 29 de setembre de 2025, 19:06:11
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "enemigo.h"

Psi* ene_new(u1 nn,u1 vida) {
	Psi* p=NULL;
	if(vida) {
		p=psi_new(nn);
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
		if(p->ha_luchado) p->ha_luchado=0;
		else if(!coger(p)) paseo(p);
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
	u2 enehere=0;
	for(u1 k=0;k<psis && enehere==0;k++) {
		Psi* pe=psi+k;
		if(pe != p && pe->x==p->x && pe->y==p->y && pe->jugador==0) enehere++;
	}
	u1 ataque=(enehere>0) || p->fuerza>protagonista->fuerza || (p->fuerza==protagonista->fuerza && p->habilidad<protagonista->habilidad);
	if(!ataque && protagonista->habilidad>p->habilidad) ataque=rand()%2;
	Psi* ap[]={protagonista};
	return (ataque)?psi_atak(p,protagonista):psi_huir(p,1,ap);
}

typedef struct {
	char* nombre;
	u1 fuerza,habilidad,capacidad;
	u1 vida_minima;
	u1 cantidad;
} Raza;

static void raza_new(Raza r) {
	u2 code;
	u1 cuenta=1;
	for(u1 k=0;k<r.cantidad;k++) {
		if(r.cantidad>1) {
			Nombre n;
			sprintf(n,"%s #%i",r.nombre,cuenta++);
			nom_new(n,&code);
		} else nom_new(r.nombre,&code);
		u1 dif=9-r.vida_minima;
		u1 vida=(dif==0)?r.vida_minima:(r.vida_minima)+rand()%dif;
		Psi* p=ene_new(code,vida);
		p->fuerza=r.fuerza;
		p->habilidad=r.habilidad;
		p->capacidad=r.capacidad;
		psi_rnd_pos(p);
	}
}

void ene_def() {
	Raza r[]={{"Rata",1,1,0,1,18},{"Serpiente",2,2,0,1,16},{"Goblin",3,2,1,3,14},{"Orco",5,2,3,4,12},{"Troll",7,0,6,5,6},{"Elfo Negro",6,8,4,9,10},{"Gigante",9,2,5,7,4},{"Dragon",9,9,0,9,1},{"Jinete Negro",9,7,3,9,3},{"Sauron",8,9,3,9,1}};
	u1 rs=10;
	for(u1 k=0;k<rs;k++) {
		raza_new(r[k]);
	}
}
