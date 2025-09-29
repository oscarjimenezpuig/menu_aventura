/*
============================================================
  Fichero: psi.c
  Creado: 25-09-2025
  Ultima Modificacion: dilluns, 29 de setembre de 2025, 19:14:15
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "psi.h"

Psi psi[PSIS];
u2 psis=0;

Psi* psi_new(u1 n) {
	if(psis<PSIS) {
		Psi* p=psi+psis;
		psis++;
		p->nombre=n;
		p->contenidos=0;
		p->oro=0;
		p->jugador=0;
		p->ha_luchado=0;
		return p;
	}
	return NULL;
}

u1 psi_ins_obj(Psi* p,Objeto* o) {
	if(p->contenidos<p->capacidad) {
		obj_pur(o);
		if(o->tipo!=TESORO) {
			p->contenido[p->contenidos++]=o;
		} else {
			p->oro+=o->valor;
		}	
		return 1;
	}
	return 0;
}

u1 psi_cog_obj(Psi* p,Objeto* o) {
	if(o->x==p->x && o->y==p->y) return psi_ins_obj(p,o);
	return 0;
}

u1 psi_hav_obj(Psi* p,Objeto* o,u1* pos) {
	for(u1 n=0;n<p->contenidos;n++) {
		if(o==p->contenido[n]) {
			if(pos) *pos=n;
		}
		return 1;
	}
	return 0;
}

u1 psi_dej_obj(Psi* p,Objeto* o) {
	u1 pos;
	if(psi_hav_obj(p,o,&pos)) {
		o->x=p->x;
		o->y=p->y;
		for(u1 k=pos;k<p->contenidos-1;k++) {
			p->contenido[k]=p->contenido[k+1];
		}
		p->contenidos--;
		return 1;
	}
	return 0;
}

void psi_pur(Psi* p) {
	p->x=MAPW;
	p->y=MAPH;
}

static void prot_visit(Psi* p) {
	if(p->jugador) map[p->x][p->y]|=VISIT;
}

void psi_rnd_pos(Psi* p) {
	p->x=rand()%MAPW;
	p->y=rand()%MAPH;
	prot_visit(p);
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
		prot_visit(p);
		return 1;
	}
	return 0;
}

u1 psi_is_alv(Psi* p) {
	return (p->x!=MAPW && p->y!=MAPH);
}

static Objeto* arma(Psi* a,u1 subtipo) {
	Objeto* aa=NULL;
	for(u1 k=0;k<a->contenidos;k++) {
		Objeto* oe=a->contenido[k];
		if(oe->tipo==ARMA && oe->subtipo==subtipo) {
			if(!aa || oe->plus>aa->plus || (oe->plus==aa->plus && oe->duracion>aa->duracion)) {
				aa=oe;
			}
		}
	}
	return aa;
}
	
u1 psi_atak(Psi* a,Psi* b) {
	printf("%s ataca a %s...\n",nombre[a->nombre],nombre[b->nombre]);
	Objeto* ara=arma(a,ATAQUE);
	u1 aa=a->fuerza+((ara!=NULL)?ara->plus:0);
	Objeto* arb=arma(b,DEFENSA);
	u1 bb=b->fuerza+((arb!=NULL)?arb->plus:0);
	u1 total=aa+bb;
	u1 dados=(total==0)?0:rand()%total;
	if(dados<aa) {
		printf("El ataque de %s es bueno...\n",nombre[a->nombre]);
		u1 golpeo=aa-dados;
		if(arb) {
			printf("El arma de defensa %s de %s absorve parte del golpe...\n",nombre[arb->nombre],nombre[b->nombre]);
			if(golpeo>=arb->duracion) {
				arb->duracion=0;
				printf("%s se ha roto...\n",nombre[arb->nombre]);
				golpeo-=arb->duracion;
				psi_dej_obj(b,arb);
				obj_pur(arb);
				arb->duracion=0;
			} else {
				arb->duracion-=golpeo;
				golpeo=0;
			}
		}
		if(golpeo) {
			if(golpeo>b->vida) golpeo=b->vida;
			printf("%s recibe un golpe de %i puntos de %s...\n",nombre[b->nombre],golpeo,nombre[a->nombre]);
			b->vida-=golpeo;
			if(b->vida==0) return psi_die(b);
			return 1;
		} else return 0;
	} else {
		printf("El ataque de %s es rechazado por %s...\n",nombre[a->nombre],nombre[b->nombre]);
		u1 diferencia=dados-bb;
		if(diferencia) {
			if(ara) {
				if(diferencia<ara->duracion) {
					printf("El arma de ataque %s de %s resulta afectada...\n",nombre[ara->nombre],nombre[a->nombre]);
					ara->duracion-=diferencia;
				} else {
					printf("El arma de ataque %s se ha roto despues del ataque fallido...\n",nombre[ara->nombre]);
					psi_dej_obj(a,ara);
					obj_pur(ara);
					ara->duracion=0;
				}
			}
		}
		return 0;
	}
}


static u1 psi_huir_uno(Psi* a,Psi* b) {
	u1 total=a->habilidad+b->habilidad;
	u1 dados=(total==0)?0:rand()%total;
	return dados<=a->habilidad;
}

u1 psi_huir(Psi* a,u1 bs,Psi* b[]) {
	printf("%s intenta huir ",nombre[a->nombre]);
	for(u1 n=0;n<bs;n++) {
		if(!psi_huir_uno(a,b[n])) {
			printf("pero %s lo captura...\n",nombre[b[n]->nombre]);
			return psi_atak(b[n],a);
		}
	}
	puts("y finalmente lo consigue...");
	u1 dir=0;
	u1 sal=map[a->x][a->y];
	while(!dir) {
		u1 ndir=rand()%4;
		dir=NORTE<<ndir;
		dir=(dir & sal)?dir:0;
	}
	psi_mov(a,dir);
	return 1;
}

u1 psi_die(Psi* p) {
	u2 x=p->x;
	u2 y=p->y;
	psi_pur(p);
	if(p->jugador) {
		puts("Has muerto...");
		quit=1;
	} else {
		printf("%s ha muerto...\n",nombre[p->nombre]);
		if(p->oro) {
			printf("Deja %i monedas de oro que recoges...\n",p->oro);
			protagonista->oro+=p->oro;
			p->oro=0;
		}
		if(p->contenidos) {
			puts("En el cadaver puedes ver: ");
			for(u1 k=0;k<p->contenidos;k++) {
				Objeto* oe=p->contenido[k];
				oe->x=x;
				oe->y=y;
				printf("\t- %s.\n",nombre[oe->nombre]);
			}
		}
	}
	return 1;
}

void psi_prt(Psi* p) {
	printf("%s (F:%i H:%i C:%i V:%i)",nombre[p->nombre],p->fuerza,p->habilidad,p->capacidad,p->vida);
}

