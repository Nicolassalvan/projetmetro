#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "aqrtopo.h"
#include "connexion.h"
#include "coord.h"
#include "liste.h"
#include "station.h"
#include "truc.h"

int main(void)
{
	Un_elem *liste = NULL, *tmp = NULL;
	liste = lire_stations("type.csv");
	tmp = liste;
	while (tmp != NULL) {
		printf("%s\n", tmp->truc->data.sta.nom);
		tmp = tmp->suiv;
	}
	FILE *fic=fopen("liste.csv", "w");
	ecrire_liste(fic, liste);
	printf("\n");
	Un_nabr *racine = construire_abr(liste);
	Un_truc *chose;
	char* nom="Pont de Levallois Bécon";
	chose = chercher_station(racine, nom);
	if (chose==NULL) {
		printf("\nNon trouvée %s\n", nom);
	}
	else {
		printf("\nYes: %s\n", chose->data.sta.nom);
	}
	detruire_abr(racine);
	detruire_liste_et_truc(liste);
	return 0;
}