/*
============================================================
  Fichero: mapa.c
  Creado: 25-09-2025
  Ultima Modificacion: dijous, 25 de setembre de 2025, 20:31:01
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

static u1 decide(u2 x,u2 y) {
	if(x==MAPW-1 && y==MAPH-1) return 0;
	if(x==MAPW-1) return SUR;
	else if(y==MAPH-1) return ESTE;
	else return (rand()%2)?SUR:ESTE;
}

static void way_new(u2 x,u2 y) {
	Way w={0,x,y};
	int px,py;
	px=x;
	py=y;
	while(1) {
		u1 dir=decide(px,py);
		if(dir) {
			w.d[w.l++]=dir;
			adv(dir,&px,&py);
			if(map[px][py]!=0) break;
		} else break;
	}
	px=x;
	py=y;
	for(u2 n=0;n<w.l;n++) {
		u1 dir=w.d[n];
		map[px][py]|=dir;
		adv(w.d[n],&px,&py);
		map[px][py]|=(8/dir);
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


