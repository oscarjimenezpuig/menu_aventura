/*
============================================================
  Fichero: protagonista.h
  Creado: 25-09-2025
  Ultima Modificacion: vie 26 sep 2025 08:52:57
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "psi.h"

#define PUNSINI 10

extern Psi* protagonista;
extern u1 quit;

char* input(u1 len,char* str);

u1 menu(char* cabecera,char* pregunta,u1 opciones,char* opcion[]);

void prot_ini();

void prot_prt();

u1 prot_ord();






#endif //PROTAGONISTA_H
