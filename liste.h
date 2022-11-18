#ifndef LISTE_H
#define LISTE_H
#include "truc.h"

typedef struct _un_elem {
	Un_truc *truc; //Une satation ou une connexion
	struct _un_elem *suiv;
} Un_elem;

Un_elem *lire_stations(char* nom_fichier);
Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc);
void detruire_liste(Un_elem *liste);
void detruire_liste_et_truc(Un_elem *liste);
void limite_zones(Un_elem* liste, Une_coord* limite_no, Une_coord* limite_se);
void ecrire_liste(FILE *flux, Un_elem *liste);

#endif