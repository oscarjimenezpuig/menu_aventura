/*
============================================================
  Fichero: entrada.c
  Creado: 27-09-2025
  Ultima Modificacion: lun 29 sep 2025 12:25:55
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "entrada.h"

void copy(char* d,char* o) {
	char* po=o;
	char* pd=d;
	while(*po!='\0') {
		*pd++=*po++;
	}
	*pd='\0';
}

char* input(u1 l,char* s) {
	char* p=s;
	char c=0;
	while((c=getchar())!='\n' && p-s<l) {
		*p++=c;
	}
	*p='\0';
	return s;
}

Menu menu_new(char* c,char* p) {
	Menu m;
	copy(m.cabecera,c);
	copy(m.pregunta,p);
	m.opciones=0;
	return m;
}

void menu_ins(Menu* m,char* o) {
	if(m->opciones<OPCIONES) {
		copy(m->opcion[m->opciones],o);
		m->opciones++;
	}
}

u1 menu_use(Menu m) {
	printf("%s\n",m.cabecera);
	for(u1 k=0;k<m.opciones;k++) {
		printf("%i. %s",k+1,m.opcion[k]);
		if(k==5) puts("");
		else printf("    ");
	}
	u1 rp=0;
	puts("");
	while(rp==0 || rp>m.opciones) {
		printf("%s ",m.pregunta);
		char str[4];
		input(3,str);
		sscanf(str,"%hhi",&rp);
	}
	return (rp-1);
}

void cenefa(char c) {
	for(u1 k=0;k<TERMW;k++) printf("%c",c);
	puts("");
}

