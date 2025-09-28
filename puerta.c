/*
============================================================
  Fichero: puerta.c
  Creado: 28-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 07:29:50
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "puerta.h"

Puerta puerta[PUERTAS];

void puer_ini() {
	Nombre n[]={"SALIDA","TIENDA"};
	u1 t[]={SALIDA,TIENDA};
	u2 ox,oy;
	for(u1 k=0;k<PUERTAS;k++) {
		nom_new(n[k],&puerta[k].nombre);
		puerta[k].tipo=t[k];
		puerta[k].abierta=0;
		u1 ok=0;
		u2 x,y;
		while(!ok) {
			x=rand()%MAPW;
			y=rand()%MAPH;
			if(k==0) {
				ox=x;
				oy=y;
				ok=1;
			} else if(x!=ox || y!=oy) ok=1;
		}
		puerta[k].x=x;
		puerta[k].y=y;
	}
}

void puer_sal() {
	puts("Esta puerta conduce a la SALIDA...");
	printf("Ahora mismo tienes %i monedas de oro...\n",protagonista->oro);
	printf("Estas seguro que quieres salir (S/n)? ");
	char r[2];
	input(1,r);
	if(*r=='S') {
		printf("Escapas de la mazmorra con %i monedas de oro...\n",protagonista->oro);
		quit=1;
	} else {
		puts("Perfecto... Creo que puedes conseguir un mayor premio antes de salir...");
	}
}

void puer_tie() {
	const u2 PREBAS=100; //precio basico de todos las caracteristicas
	const u2 PREVID=200; //precio maximo de la vida
	char* const SCAR[]={"Fuerza","Habilidad","Capacidad","Vida"};
	static u2 precios[4];
	static u1 primera=1;
	static Menu meco;
	u1* carpro[]={&(protagonista->fuerza),&(protagonista->habilidad),&(protagonista->capacidad),&(protagonista->vida)};
	meco.opciones=0;
	if(primera) {
		precios[0]=precios[1]=precios[2]=PREBAS;
		precios[3]=1+(rand()%PREVID);
		meco=menu_new("Articulos disponibles: ","Que quieres comprar?");
		primera=0;
	}
	puts("Bienvenido a la TIENDA!!!");
	puts("Este es el listado de precios actuales:");
	for(u1 k=0;k<4;k++) {
		printf("\t%s: %i monedas de oro.\n",SCAR[k],precios[k]);
	}
	for(u1 k=0;k<4;k++) {
		menu_ins(&meco,SCAR[k]);
	}
	u1 ok;
	do {
		menu_ins(&meco,"Nada");
		u1 np=menu_use(meco);
		if(np==4) {
			puts("De acuerdo... Otra vez sera!!!");
		} else {
			if(protagonista->oro>=precios[np]) {
				if(*carpro[np]<9) {
					printf("Comprado, aumentas %s en +1...\n",SCAR[np]);
					*carpro[np]+=1;
					protagonista->oro-=precios[np];
					printf("Ahora te quedan %i monedas de oro.\n",protagonista->oro);
					if(np==3) precios[np]=1+(rand()%PREVID);
					else precios[np]=2*precios[np];
				} else puts("Esta caracteristica ya ha llegado al maximo de la puntuacion...");
			} else puts("No tienes suficiente dinero...");
			printf("Alguna cosa mas (S/n)? ");
			char r[2];
			input(1,r);
			ok=(*r=='S');
		}
	}while(ok);
	puts("Abandonas la tienda...");
}

void puer_prt(Puerta* p) {
	printf("Hay una puerta donde pone %s, esta %s.",nombre[p->nombre],(p->abierta)?"abierta":"cerrada");
}	
	
	

				

	


