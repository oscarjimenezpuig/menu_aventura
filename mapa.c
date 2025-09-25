/*
============================================================
  Fichero: mapa.c
  Creado: 25-09-2025
  Ultima Modificacion: jue 25 sep 2025 12:26:12
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "mapa.h"

u1 map[MAPW][MAPH];

typedef struct {
	u2 l;
	u2 x,y;
	u1 d[MAPW+MAPH];
} Way;

static void adv(u1 dir,int* x,int* y) {
	*x=(dir==ESTE)?*x+1:*x;
	*y=(dir==SUR)?*y+1:*y;
}

static void way_new(u2 x,u2 y) {
	Way w={0,x,y};
	int px,py;
	px=x;
	py=y;
	u1 stop=0;
	printf("Camino\n");//dbg
	while(!stop) {
		if(px>=0 && px<MAPW && py>=0 && py<MAPH && map[px][py]==0) {
			u1 dir=(rand()%2)?SUR:ESTE;
			printf("%i,%i [%i]->",px,py,dir);//dbg
			w.d[w.l++]=dir;
			adv(dir,&px,&py);
		} else stop=1;
	}
	printf("\n");//dbg
	px=x;
	py=y;
	for(u2 n=0;n<w.l;n++) {
		map[px][py]|=w.d[n];
		adv(w.d[n],&px,&py);
		map[px][py]|=(8/w.d[n]);
	}
}

void map_ini() {
	u2 x=rand()%MAPW;
	u2 y=rand()%MAPH;
	way_new(x,y);
	for(x=0;x<MAPW;x++) {
		for(y=0;y<MAPH;y++) {
			if(map[x][y]==0) {
				way_new(x,y);
			}
		}
	}
}

void map_prt() {
	for(u2 y=0;y<MAPH;y++) {
		for(u2 x=0;x<MAPW;x++) {
			printf("%02i ",map[x][y]);
		}
		printf("\n");
	}
}

//prueba

int main() {
	map_ini();
	map_prt();
	return 0;
}

