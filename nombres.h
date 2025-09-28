/*
============================================================
  Fichero: nombres.h
  Creado: 27-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 05:59:09
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef NOMBRES_H
#define NOMBRES_H

#define NOMLEN 20
#define NOMBRES 202

#include "entrada.h"

typedef char Nombre[NOMLEN];

extern Nombre nombre[NOMBRES];
extern u1 nombres;

u1 nom_new(Nombre nombre,u2* posicion);

#endif //NOMBRES_H

