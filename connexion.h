#include "ligne.h"

#ifndef CONNEXION_H
#define CONNEXION_H

typedef struct _une_connexion{
	struct _un_truc *sta_dep; //Station de depart
	struct _un_truc *sta_arr; //Station d'arrivée
	struct _une_ligne *ligne; //Ligne
}Une_connexion;

#endif