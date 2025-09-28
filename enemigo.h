/*
============================================================
  Fichero: enemigo.h
  Creado: 27-09-2025
  Ultima Modificacion: diumenge, 28 de setembre de 2025, 07:09:22
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "puerta.h"

Psi* ene_new(char* nombre,u1 vida);

u1 ene_act(Psi* p);
//actuacion si no esta muerto (en el purgatorio)

u1 enes_act();
//actuan todos los enemigos uno detras de otro

u1 ene_enc(Psi* p);
//el enemigo encuentra al protagonista

#endif //ENEMIGO_H
