/*
============================================================
  Fichero: protagonista.c
  Creado: 25-09-2025
  Ultima Modificacion: dijous, 25 de setembre de 2025, 20:55:10
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "protagonista.h"

Psi* protagonista=NULL;

char* input(u1 l,char* s) {
	char* p=s;
	char c=0;
	while((c=getchar())!='\n' && p-s<l) {
		*p++=c;
	}
	*p='\0';
	return s;
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
	if(sl & NORTE) printf("Norte");
	if(sl & SUR) printf("Sur");
	if(sl & ESTE) printf("Este");
	if(sl & OESTE) printf("Oeste");
	puts("");
	printf("Aqui puedes ver: ");
	u1 algo=0;
	for(u1 n=0;n<objetos;n++) {
		if(objeto[n].x==x && objeto[n].y==y) {
			algo++;
			printf("%s ",objeto[n].nombre);
		}
	}
	if(!algo) printf("Nada interesante");
	puts("");
}
		
//prueba

int main() {
	map_ini();
	prot_ini();
	prot_prt();

	return 0;
}

