/*
============================================================
  Fichero: psi.h
  Creado: 25-09-2025
  Ultima Modificacion: mar 30 sep 2025 08:53:14
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#ifndef PSI_H
#define PSI_H

#include "objeto.h"

#define PSIS (((NOMBRES-OBJETOS)<0)?0:(NOMBRES-OBJETOS))
#define MAXPUN 10

typedef signed char i1;

typedef struct {
	u2 nombre;
	u2 x,y;
	u1 jugador;
	u1 fuerza;
	u1 habilidad;
	u1 capacidad;
	u2 oro;
	u1 vida;
	u1 ha_luchado;
	u1 contenidos;
	Objeto* contenido[MAXPUN];
} Psi;

extern Psi psi[PSIS];
extern u2 psis;

extern Psi* protagonista;
extern u1 quit;
extern u2 enemigos;
extern u2 muertos;
extern Psi* muerto_importante;

Psi* psi_new(u1 nombre);

u1 psi_ins_obj(Psi* psi,Objeto* obj);
//insertar objeto (independientemente de donde este) no ha de superar capacidad de psi

u1 psi_cog_obj(Psi* psi,Objeto* obj);
//coger objeto, es como insertar pero el objeto ha de estar en la posicion del psi

u1 psi_hav_obj(Psi* psi,Objeto* obj,u1* n);
//dice si un objeto esta o no en el psi y da la posicion

u1 psi_dej_obj(Psi* psi,Objeto* obj);
//dejamos el objeto si esta en el

void psi_pur(Psi* p);
//envia al psi al purgatorio

void psi_rnd_pos(Psi* psi);

u1 psi_mov(Psi* p,u1 dir);

u1 psi_is_alv(Psi* p);
//dice si un psi esta vivo

u1 psi_atak(Psi* a,Psi* b);
//lucha entre a y b

u1 psi_huir(Psi* a,u1 bs,Psi* b[]);
//a intenta huir de todos los b`s (si no, lo golpea)

u1 psi_die(Psi* p);
//muerte de cualquier psi

void psi_prt(Psi* p);

#endif //PSI_H
