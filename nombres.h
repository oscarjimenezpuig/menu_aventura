/*
============================================================
  Fichero: nombres.h
  Creado: 27-09-2025
  Ultima Modificacion: dilluns, 29 de setembre de 2025, 19:06:11
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef NOMBRES_H
#define NOMBRES_H

#define NOMLEN 20
#define NOMBRES 302

#include "entrada.h"

typedef char Nombre[NOMLEN];

extern Nombre nombre[NOMBRES];
extern u1 nombres;

u1 nom_new(Nombre nombre,u2* posicion);

#endif //NOMBRES_H

