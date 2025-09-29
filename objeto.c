/*
============================================================
  Fichero: objeto.c
  Creado: 25-09-2025
  Ultima Modificacion: lun 29 sep 2025 12:04:30
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "objeto.h"

u1 objetos=0;
Objeto objeto[OBJETOS];

Objeto* obj_new(u2 nn) {
	if(objetos<OBJETOS) {
		Objeto* o=objeto+objetos;
		o->nombre=nn;
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

static void llav_def() {
	char* nllave[]={"Llave de oro","Llave de plata","Llave de cobre"};
	u1 usado[]={0,0,0};
	for(u1 k=0;k<3;k++) {
		u2 code;
		nom_new(nllave[k],&code);
		Objeto* o=obj_new(code);
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

static void pla_def() {
	u2 code;
	Nombre np="Plano";
	nom_new(np,&code);
	Objeto* o=obj_new(code);
	o->tipo=MAPA;
	obj_rnd_pos(o);
};

typedef struct {
	char* nombre;
	u1 subtipo;
	u1 plus;
	u1 duracion_minima;
	u1 cantidad;
} TipoArma;

static void tarm_def_one(TipoArma t) {
	u2 code;
	nom_new(t.nombre,&code);
	for(u1 k=0;k<t.cantidad;k++) {
		Objeto* o=obj_new(code);
		o->tipo=ARMA;
		o->subtipo=t.subtipo;
		o->plus=t.plus;
		u1 dur=(t.duracion_minima==9)?9:t.duracion_minima+rand()%(9-t.duracion_minima);
		o->duracion=dur;
		obj_rnd_pos(o);
	}
}
	
static void tarm_def() {
	TipoArma ta[]={{"Navaja",ATAQUE,1,3,7},{"Cuchillo",ATAQUE,2,4,6},{"Espada",ATAQUE,3,5,5},{"Sable",ATAQUE,4,5,4},{"Espada Larga",ATAQUE,5,6,3},{"Hacha",ATAQUE,6,8,2},{"Rodela de madera",DEFENSA,1,2,7},{"Rodela de hierro",DEFENSA,2,5,6},{"Escudo de madera",DEFENSA,3,3,5},{"Escudo de hierro",DEFENSA,4,7,4},{"Cota de malla",DEFENSA,5,7,3},{"Cota de Mithril",DEFENSA,9,9,1}};
	u1 tas=12;
	for(u1 k=0;k<tas;k++) tarm_def_one(ta[k]);
}

static void tes_def() {
	const u2 ORO=10000;
	const u2 COFRES=50;
	const u2 ORPCO=ORO/COFRES;
	u2 oro=ORO;
	Nombre n="Cofre";
	u2 code;
	nom_new(n,&code);
	while(oro) {
		u2 oec=(rand()% ORPCO)+ORPCO;
		oro-=ORPCO;
		Objeto* o=obj_new(code);
		o->tipo=TESORO;
		o->valor=oec;
		obj_rnd_pos(o);
	}
}

void obj_def() {
	llav_def();
	pla_def();
	tarm_def();
	tes_def();
}


		
