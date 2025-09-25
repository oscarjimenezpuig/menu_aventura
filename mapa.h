/*
============================================================
  Fichero: mapa.h
  Creado: 25-09-2025
  Ultima Modificacion: jue 25 sep 2025 12:17:07
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef MAPA_H
#define MAPA_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAPW 3
#define MAPH 3

#define NORTE 1
#define SUR 8
#define OESTE 2
#define ESTE 4

typedef unsigned char u1;
typedef unsigned short u2;

extern u1 map[MAPW][MAPH];

void map_ini();

void map_prt();

#endif //MAPA_H
