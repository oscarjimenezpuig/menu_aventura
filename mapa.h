/*
============================================================
  Fichero: mapa.h
  Creado: 25-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 09:21:57
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef MAPA_H
#define MAPA_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "nombres.h"

#define MAPW 3
#define MAPH 3

#define NORTE 1
#define SUR 8
#define OESTE 2
#define ESTE 4

#define VISIT 128

extern u1 map[MAPW][MAPH];

void map_ini();

void map_prt(u2 x,u2 y);

#endif //MAPA_H
