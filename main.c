#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "abr.h"
#include "aqrtopo.h"
#include "connexion.h"
#include "coord.h"
#include "liste.h"
#include "station.h"
#include "truc.h"
#include "ligne.h"

int main(void)
{
	// Vérification : liste_connexions (exercice 4)
	Une_ligne *lignes, *zebi;
	Un_elem *l_con;
	Un_elem *l_sta;
	Un_nabr *abr_sta;
	l_sta = lire_stations("liste_station.csv");
	abr_sta = construire_abr(l_sta);
	lignes = lire_lignes("liste_ligne.csv");
	afficher_lignes(lignes);
	l_con = lire_connexions("liste_connexion.csv", lignes, abr_sta);
	if (l_con==NULL) {
		printf("Gros FAIL\n");
	}
	/*
	// On vérifie que la liste de connexion a été faite
	Un_elem *tmpcon = l_con;
	while (tmpcon != NULL) {
		printf("%s ; %s ; %s\n", tmpcon->truc->data.con.ligne->code, tmpcon->truc->data.con.sta_dep->data.sta.nom, tmpcon->truc->data.con.sta_arr->data.sta.nom);
		tmpcon = tmpcon->suiv;
	}
	*/
	// On vérifie que le Tab_con a été modifié pour chaque station:
	Un_elem* tmpsta=l_sta;
	int n;
	int i;
	printf("\nVERIFICATION TABCON\n\n");
	while (tmpsta !=NULL) {
		printf("nb connexion=%d, Sta: %s\n", tmpsta->truc->data.sta.nb_con, tmpsta->truc->data.sta.nom);
		printf("--> ");
		for (i=0 ; i < tmpsta->truc->data.sta.nb_con ; i++ ) {
			printf("%s\t", tmpsta->truc->data.sta.Tab_con[i]->data.con.sta_arr->data.sta.nom);
		}	
		printf("\n\n");
		tmpsta = tmpsta->suiv;
	}
	// On vérifie que chaque intervalle de chaque ligne est maintenant non nul
	printf("VERIFICATION DE LA MODIFICATION DE INTERVALLE\n");
	Une_ligne *tmpligne = lignes;
	while (tmpligne !=NULL) {
		printf("Ligne %s: intervalle de %f min\n", tmpligne->code, tmpligne->intervalle);
		tmpligne = tmpligne->suiv;
	}
	detruire_abr(abr_sta);
	return 0;
}