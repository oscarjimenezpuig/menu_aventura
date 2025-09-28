/*
============================================================
  Fichero: entrada.h
  Creado: 27-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 11:21:50
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef ENTRADA_H
#define ENTRADA_H

#include <stdlib.h>
#include <stdio.h>

#define MENULEN 256
#define OPCIONES 256
#define TERMW 80

typedef unsigned char u1;
typedef unsigned short u2;


typedef struct {
	char cabecera[MENULEN];
	char pregunta[MENULEN];
	u1 opciones;
	char opcion[MENULEN][OPCIONES];
} Menu;

void copy(char* d,char* o);

char* input(u1 len,char* str);

Menu menu_new(char* cabecera,char* pregunta);

void menu_ins(Menu* m,char* opcion);

u1 menu_use(Menu m);

void cenefa(char c);

#endif //ENTRADA_H

