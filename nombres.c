/*
============================================================
  Fichero: nombres.c
  Creado: 27-09-2025
  Ultima Modificacion: dissabte, 27 de setembre de 2025, 19:15:44
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "nombres.h"

Nombre nombre[NOMBRES];
u1 nombres=0;

u1 nom_new(Nombre n,u2* pos) {
	if(nombres<NOMBRES) {
		copy(nombre[nombres],n);
		*pos=nombres;
		nombres++;
		return 1;
	}
	return 0;
}



