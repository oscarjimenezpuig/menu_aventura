/*
============================================================
  Fichero: protagonista.c
  Creado: 25-09-2025
  Ultima Modificacion: vie 26 sep 2025 12:28:18
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "protagonista.h"

Psi* protagonista=NULL;
u1 quit=0;

static u1 tipo_menu=1;

char* input(u1 l,char* s) {
	char* p=s;
	char c=0;
	while((c=getchar())!='\n' && p-s<l) {
		*p++=c;
	}
	*p='\0';
	return s;
}

u1 menu(char* c,char* p,u1 os,char* o[]) {
	printf("%s\n",c);
	for(u1 n=0;n<os;n++) {
		printf("\t%i. %s.\n",n+1,o[n]);
	}
	u1 nr=0;
	do {
		printf("%s ",p);
		char r[3];
		input(2,r);
		sscanf(r,"%hhi",&nr);
	}while(nr>os);
	return nr-1;
}

void prot_ini() {
	printf("Introduce el nombre del protagonista: ");
	char n[NOMLEN];
	input(NOMLEN-1,n);
	protagonista=psi_new(n);
	if(protagonista) {
		char* caract[]={"fuerza","agilidad","capacidad"};
		u1 points[3];
		u1 ok=0;
		puts("Ahora definiras las caracteristicas del protagonista.");	
		printf("%s, tienes %i puntos para repartir entre tres caracteristicas\n",protagonista->nombre,PUNSINI);
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
			printf("Estas de acuerdo (s/N)? )");
			char r[2];
			input(1,r);
			if(*r!='N') ok=1;
		}
		protagonista->fuerza=points[0];
		protagonista->agilidad=points[1];
		protagonista->capacidad=points[2];
		psi_rnd_pos(protagonista);
		protagonista->vida=10;
	}
}

void prot_prt() {
	int x=protagonista->x;
	int y=protagonista->y;
	printf("Estas en la habitacion %i.\n",x+MAPW*y);
	printf("Esta habitacion tiene salidas: ");
	u1 sl=map[x][y];
	if(sl & NORTE) printf("Norte ");
	if(sl & SUR) printf("Sur ");
	if(sl & ESTE) printf("Este ");
	if(sl & OESTE) printf("Oeste");
	puts("");
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

static u1 prot_mov(u1 rp) {
	u1 dir=(rp==0)?NORTE:(rp==1)?SUR:(rp==2)?ESTE:OESTE;
	u1 reac=psi_mov(protagonista,dir);
	if(!reac) puts("No puedes ir hacia alli...");
	return reac;
}

static u1 prot_cog() {
	if(protagonista->contenidos<protagonista->capacidad) {
		u1 items=0;
		char* nitem[objetos];
		u1 iitem[objetos];
		for(u1 n=0;n<objetos;n++) {
			Objeto oe=objeto[n];
			if(oe.x==protagonista->x && oe.y==protagonista->y) {
				nitem[items]=oe.nombre;
				iitem[items]=n;
				items++;
			}
		}
		if(items) {
			u1 nr=menu("Objetos disponibles","Que objeto quieres coger?",items,nitem);
			Objeto* oe=objeto+iitem[nr];
			psi_ins_obj(protagonista,oe);
			if(oe->tipo==ARMA) puts("Arma cogida...");
			else printf("Has conseguido %i monedas de oro...\n",oe->valor);
			return 1;
		} else {
			puts("No veo nada que pueda coger aqui...");
		}
	} else puts("No puedo coger nada mas...");
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
	}
	return 1;
}

static u1 finalizar() {
	quit=1;
	return 1;
}

static u1 menu_1_accion() {
	char* c="Las acciones disponibles son:";
	char* p="Que quieres hacer?";
	char* op[]={"Descansar","Inventario","Coger"};
	u1 ops=3;
	u1 rp=menu(c,p,ops,op);
	switch(rp) {
		case 0:
			return prot_des();
		case 1:
			return prot_inv();
		case 2:
			return prot_cog();
		default:
			puts("OPCIONES NO PROGRAMADAS");
	}
	return 0;
}


static u1 menu_1() {
	char* c="Que quieres hacer?";
	char* p="Introduce una opcion:";
	char* op[]={"Norte","Sur","Este","Oeste","Accion","Finalizar"};
	u1 ops=6;
	u1 rp=menu(c,p,ops,op);
	switch(rp) {
		case 0:
		case 1:
		case 2:
		case 3:
			return prot_mov(rp);
		case 4:
			return menu_1_accion();
		case 5:
			return finalizar();
		default:
			puts("OPCIONES NO PROGRAMADAS");
	}
	return 0;
}

u1 prot_ord() {
	if(tipo_menu==1) return menu_1();
	else puts("NO HAY MAS MENUS PROGRAMADOS");
	return 0;
}

		
//prueba

void obj_def() {
	Objeto* es=obj_new("Espada");
	es->tipo=ARMA;
	es->subtipo=ATAQUE;
	es->plus=1;
	obj_rnd_pos(es);
	Objeto* te=obj_new("Cofre");
	te->tipo=TESORO;
	te->valor=100;
	obj_rnd_pos(te);
}

int main() {
	map_ini();
	prot_ini();
	obj_def();
	while(!quit) {
		prot_prt();
		prot_ord();
	}
	return 0;
}

