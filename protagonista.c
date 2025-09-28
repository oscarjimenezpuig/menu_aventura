/*
============================================================
  Fichero: protagonista.c
  Creado: 25-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 11:23:10
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "protagonista.h"

Psi* protagonista=NULL;
u1 quit=0;

static u1 tipo_menu=0;
static u1 hay_enemigos=0;

void prot_ini() {
	printf("Introduce el nombre del protagonista: ");
	char n[NOMLEN];
	input(NOMLEN-1,n);
	protagonista=psi_new(n);
	if(protagonista) {
		char* caract[]={"fuerza","habilidad","capacidad"};
		u1 points[3];
		u1 ok=0;
		puts("Ahora definiras las caracteristicas del protagonista.");	
		printf("%s, tienes %i puntos para repartir entre tres caracteristicas\n",nombre[protagonista->nombre],PUNSINI);
		while(!ok) {
			u1 puntos=PUNSINI;
			for(u1 n=0;n<3;n++) {
				u1 valido=0;
				while(!valido) {
					printf("Puntos restantes: %i\n",puntos);
					printf("Introduce los puntos de %s: ",caract[n]);
					char sp[4];
					input(3,sp);
					int p;
					sscanf(sp,"%i",&p);
					p=(p<0)?-p:p;
					if(p<=puntos) {
						puntos-=p;
						points[n]=p;
						valido=1;
					}
				}
			}
			puts("Las caracteristicas del jugador son: ");
			for(u1 n=0;n<3;n++) {
				printf("\tCaracteristica %s: %i\n",caract[n],points[n]);
			}
			printf("Estas de acuerdo (s/N)? ");
			char r[2];
			input(1,r);
			if(*r!='N') ok=1;
		}
		protagonista->fuerza=points[0];
		protagonista->habilidad=points[1];
		protagonista->capacidad=points[2];
		protagonista->vida=10;
		protagonista->jugador=1;
		psi_rnd_pos(protagonista);
	}
}

static u1 enemigos_find(Psi* enemigo[]) {
	u1 enemigos=0;
	for(u1 k=0;k<psis;k++) {
		Psi* p=psi+k;
		if(p->jugador==0 && p->x==protagonista->x && p->y==protagonista->y) {
			enemigo[enemigos++]=p;
		}
	}
	return enemigos;
}

void prot_prt() {
	hay_enemigos=0;
	int x=protagonista->x;
	int y=protagonista->y;
	psi_prt(protagonista);
	puts("");
	printf("Estas en la habitacion %i.\n",x+MAPW*y);
	printf("Esta habitacion tiene salidas: ");
	u1 sl=map[x][y];
	if(sl & NORTE) printf("Norte ");
	if(sl & SUR) printf("Sur ");
	if(sl & ESTE) printf("Este ");
	if(sl & OESTE) printf("Oeste");
	puts("");
	for(u1 k=0;k<PUERTAS;k++) {
		Puerta* p=puerta+k;
		if(p->x==x && p->y==y) {
			puer_prt(p);
			puts("");
			break;
		}
	}
	Psi* enem[psis];
	hay_enemigos=enemigos_find(enem);
	if(hay_enemigos) {
		puts("Atencion!! Hay enemigos en la habitacion: ");
		for(u1 k=0;k<hay_enemigos;k++) {
			printf("\t- ");
			psi_prt(enem[k]);
			puts("");
		}
	} else {
		puts ("Aqui puedes ver: ");
		u1 algo=0;
		for(u1 n=0;n<objetos;n++) {
			if(objeto[n].x==x && objeto[n].y==y) {
				algo++;
				printf("\t- ");
				obj_prt(objeto+n);
				puts("");
			}
		}
		if(!algo) printf("\tNada interesante\n");
	}
}

static u1 prot_mov(u1 rp) {
	u1 dir=(rp==0)?NORTE:(rp==1)?SUR:(rp==2)?ESTE:OESTE;
	u1 reac=psi_mov(protagonista,dir);
	if(!reac) puts("No puedes ir hacia alli...");
	return reac;
}

static u1 prot_cog() {
	static Menu mc;
	static u1 defmc=0;
	mc.opciones=0;
	if(!defmc) {
		defmc=1;
		mc=menu_new("Objetos disponibles","Que objeto quieres coger?");
	}
	if(protagonista->contenidos<protagonista->capacidad) {
		u1 items=0;
		u2 iitem[objetos];
		for(u1 n=0;n<objetos;n++) {
			Objeto oe=objeto[n];
			if(oe.x==protagonista->x && oe.y==protagonista->y) {
				menu_ins(&mc,nombre[oe.nombre]);
				iitem[items]=n;
				items++;
			}
		}
		if(items) {
			u1 nr=menu_use(mc);
			Objeto* oe=objeto+iitem[nr];
			psi_ins_obj(protagonista,oe);
			if(oe->tipo!=TESORO) puts("Cogido...");
			else printf("Has conseguido %i monedas de oro...\n",oe->valor);
			return 1;
		} else {
			puts("No veo nada que pueda coger aqui...");
		}
	} else puts("No puedo coger nada mas...");
	return 0;
}

static u1 prot_dej() {
	static Menu md;
	static u1 defmd=0;
	md.opciones=0;
	if(!defmd) {
		md=menu_new("Tienes los siguientes objetos","Que objeto quieres dejar?");
		defmd=1;
	}
	u1 cs=protagonista->contenidos;
	if(cs) {
		for(u1 n=0;n<cs;n++) {
			menu_ins(&md,nombre[protagonista->contenido[n]->nombre]);
		};
		u1 nr=menu_use(md);
		Objeto* od=protagonista->contenido[nr];
		psi_dej_obj(protagonista,od);
		puts("Dejado...");
		return 1;
	}
	puts("No tengo nada para dejar...");
	return 0;
}

static Puerta* puer_fnd() {
	Puerta* p=NULL;
	for(u1 k=0;k<PUERTAS;k++) {
		Puerta* pe=puerta+k;
		if(pe->x==protagonista->x && pe->y==protagonista->y) {
			p=pe;
			break;
		}
	}
	return p;
}

static u1 prot_abr() {
	static Menu mab;
	static u1 defmab=0;
	mab.opciones=0;
	if(!defmab) {
		mab=menu_new("Tienes las siguientes llaves:","Cual quieres usar?");
		defmab=1;
	}
	Psi* pr=protagonista;
	Puerta* p=puer_fnd();
	if(!p) puts("No hay aqui ninguna puerta que se pueda abrir...");
	else if(p->abierta) puts("Esta puerta ya esta abierta...");
	else {
		Objeto* llave[pr->contenidos];
		u1 llaves=0;
		for(u1 k=0;k<pr->contenidos;k++) {
			Objeto* oe=pr->contenido[k];
			if(oe->tipo==LLAVE) {
				llave[llaves++]=oe;
				menu_ins(&mab,nombre[oe->nombre]);
			}
		}
		if(!llaves) puts("No tienes llaves para abrir nada...");
		else {
			u1 rp=menu_use(mab);
			Objeto* lle=llave[rp];
			if(lle->lugar==p->tipo) {
				puts("Abres la puerta...");
				p->abierta=1;
				return 1;
			} else puts("Parece que esta llave no abre esta puerta...");
		}
	}
	return 0;
}

static u1 prot_ent() {
	Puerta* p=puer_fnd();
	if(!p) puts("Aqui no hay ninguna puerta...");
	else if(!p->abierta) puts("La puerta no esta abierta...");
	else {
		if(p->tipo==SALIDA) puer_sal();
		else puer_tie();
		return 1;
	}
	return 0;
}

static u1 prot_des() {
	puts("Descanso...");
	return 1;
}

static u1 prot_inv() {
	printf("Tienes %i monedas de oro y... ",protagonista->oro);
	if(protagonista->contenidos==0) puts("nada mas.");
	else {
		puts("");
		for(u1 n=0;n<protagonista->contenidos;n++) {
			printf("\t- ");
			obj_prt(protagonista->contenido[n]);
			puts("");
		}
		if(protagonista->contenidos==protagonista->capacidad) puts("Ya no puedes llevar nada mas...");
	}
	return 1;
}

static u1 prot_pla() {
	u1 has_mapa=0;
	for(u1 k=0;k<protagonista->contenidos;k++) {
		if(protagonista->contenido[k]->tipo==MAPA) {
			has_mapa=1;
			break;
		}
	}
	if(!has_mapa) puts("No tienes ningun plano...");
	else {
		puts("El plano del mapa observado es:");
		map_prt(protagonista->x,protagonista->y);
		puts("");
		return 1;
	}
	return 0;
}

static u1 finalizar() {
	quit=1;
	return 1;
}

static u1 menu_1_accion() {
	static Menu ma;
	static u1 defma=0;
	if(!defma) {
		char* c="Las acciones disponibles son:";
		char* p="Que quieres hacer?";
		char* op[]={"Descansar","Inventario","Coger","Dejar","Abrir","Entrar","Mirar plano"};
		u1 ops=7;
		ma=menu_new(c,p);
		for(u1 k=0;k<ops;k++) menu_ins(&ma,op[k]);
		defma=1;
	}
	u1 rp=menu_use(ma);
	switch(rp) {
		case 0:
			return prot_des();
		case 1:
			return prot_inv();
		case 2:
			return prot_cog();
		case 3:
			return prot_dej();
		case 4:
			return prot_abr();
		case 5:
			return prot_ent();
		case 6:
			return prot_pla();
	}
	return 0;
}

static u1 menu_0();

static u1 menu_1() {
	static Menu mu;
	static u1 defmu=0;
	if(!defmu) {
		char* c="Que quieres hacer?";
		char* p="Introduce una opcion:";
		char* op[]={"Norte","Sur","Este","Oeste","Accion","Cambiar menu","Finalizar"};
		u1 ops=7;
		mu=menu_new(c,p);
		for(u1 k=0;k<ops;k++) menu_ins(&mu,op[k]);
		defmu=1;
	}
	u1 rp=menu_use(mu);
	switch(rp) {
		case 0:
		case 1:
		case 2:
		case 3:
			return prot_mov(rp);
		case 4:
			return menu_1_accion();
		case 5:
			tipo_menu=0;
			return menu_0();
		case 6:
			return finalizar();
	}
	return 0;
}

static u1 menu_0_ir() {
	static Menu muir;
	static u1 defmuir=0;
	if(!defmuir) {
		char* c="Puedes hacer lo siguiente:";
		char* p="Donde quieres ir?";
		char* op[]={"Norte","Sur","Este","Oeste","Entrar"};
		u1 ops=5;
		muir=menu_new(c,p);
		for(u1 k=0;k<ops;k++) menu_ins(&muir,op[k]);
		defmuir=1;
	}
	u1 rp=menu_use(muir);
	switch(rp) {
		 case 0:
		 case 1:
		 case 2:
		 case 3:
			 return prot_mov(rp);
		 case 4:
			 return prot_ent();
	}
	return 0;
}

static u1 menu_0() {
	static Menu mu;
	static u1 defmu=0;
	if(!defmu) {
		char* c="Que quieres hacer?";
		char* p="Introduce una opcion:";
		char* op[]={"Ir","Descansar","Inventario","Coger","Dejar","Abrir","Mirar plano","Cambiar menu","Finalizar"};
		u1 ops=9;
		mu=menu_new(c,p);
		for(u1 k=0;k<ops;k++) menu_ins(&mu,op[k]);
		defmu=1;
	}
	u1 rp=menu_use(mu);
	switch(rp) {
		case 0:
			return menu_0_ir();
		case 1:
			return prot_des();
		case 2:
			return prot_inv();
		case 3:
			return prot_cog();
		case 4:
			return prot_dej();
		case 5:
			return prot_abr();
		case 6:
			return prot_pla();
		case 7:
			tipo_menu=1;
			return menu_1();
		case 8:
			return finalizar();
	}
	return 0;
}

static u1 menu_e_atacar(u1 enes,Psi* ene[]) {
	static Menu mea;
	static u1 defmea=0;
	mea.opciones=0;
	if(!defmea) {
		char* c="Los enemigos que puedes ver son:";
		char* p="A quien atacas?";
		mea=menu_new(c,p);
		defmea=1;
	}
	for(u1 k=0;k<enes;k++) {
		menu_ins(&mea,nombre[ene[k]->nombre]);
	}
	u1 rp=menu_use(mea);
	return psi_atak(protagonista,ene[rp]);
}

static u1 menu_e(u1 enms,Psi* enm[]) {
	static Menu me;
	static u1 defme=0;
	if(!defme) {
		char* c="Enemigos en la zona...";
		char* p="Que quieres hacer?";
		char* op[]={"Atacar","Huir"};
		u1 ops=2;
		me=menu_new(c,p);
		for(u1 k=0;k<ops;k++) menu_ins(&me,op[k]);
		defme=1;
	}
	u1 rp=menu_use(me);
	if(rp==0) return menu_e_atacar(enms,enm);
	else return psi_huir(protagonista,enms,enm);
}

static u1 prot_enc_ene() {
	u1 ret=0;
	Psi* ene[psis];
	u1 enes=enemigos_find(ene);
	if(enes>1) {
		for(u1 k=0;k<enes;k++) {
			ret|=ene_enc(ene[k]);
		}
		if(psi_is_alv(protagonista)) {
			ret|=menu_e(enes,ene);
		}
	} else if(enes==1) {
		if(ene[0]->vida>protagonista->vida) {
			ret|=ene_enc(ene[0]);
			if(psi_is_alv(protagonista)) {
				ret|=menu_e(enes,ene);
			}
		} else {
			ret|=menu_e(enes,ene);
			if(psi_is_alv(ene[0])) {
				ret|=ene_enc(ene[0]);
			}
		}
	}
	return ret;
}

u1 prot_ord() {
	if(hay_enemigos) {
		return prot_enc_ene();
	} else {
		switch(tipo_menu) {
			case 0:
				return menu_0();
			case 1:
				return menu_1();
		}
	}
	return 0;
}

		
//prueba

char* noes="Espada";
char* noco="Cofre";

void obj_def() {
	Objeto* es=obj_new(noes);
	es->tipo=ARMA;
	es->subtipo=ATAQUE;
	es->plus=1;
	es->duracion=5;
	obj_rnd_pos(es);
	Objeto* te=obj_new(noco);
	te->tipo=TESORO;
	te->valor=100;
	obj_rnd_pos(te);
}

void psi_def() {
	Psi* gb=ene_new("Goblin",5);
	gb->fuerza=3;
	gb->habilidad=5;
	gb->capacidad=2;
	psi_rnd_pos(gb);
}

int main() {
	map_ini();
	prot_ini();
	puer_ini();
	llav_ini();
	pla_ini();
	obj_def();
	psi_def();
	while(!quit) {
		cenefa('=');
		prot_prt();
		cenefa('-');
		prot_ord();
		enes_act();
	}
	return 0;
}

