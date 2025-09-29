/*
============================================================
  Fichero: enemigo.h
  Creado: 27-09-2025
  Ultima Modificacion: lun 29 sep 2025 10:48:04
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "puerta.h"

Psi* ene_new(u1 id_nombre,u1 vida);

u1 ene_act(Psi* p);
//actuacion si no esta muerto (en el purgatorio)

u1 enes_act();
//actuan todos los enemigos uno detras de otro

u1 ene_enc(Psi* p);
//el enemigo encuentra al protagonista

void ene_def();

#endif //ENEMIGO_H
