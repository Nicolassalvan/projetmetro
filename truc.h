#include "station.h"
#include "coord.h"
#include "connexion.h"

#ifndef TRUC_H
#define TRUC_H

typedef enum  _ttype{STA,CON} Ttype;

typedef union _data {
	Une_station sta;
	Une_connexion con;
}Tdata;

typedef struct _un_truc{
	Une_coord coord;
	Ttype type; //Station ou connexion
	Tdata data; 
	float user_val; //Distance pour plus court chemin
} Un_truc;

Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv);
void detruire_truc(Un_truc *truc);

#endif