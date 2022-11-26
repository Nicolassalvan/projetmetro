#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	Un_elem *liste = NULL;
	liste = lire_stations("test.csv");

	// Creation d'une ligne
	Une_ligne *ligne = (Une_ligne*) malloc(sizeof(Une_ligne));
	ligne->code = (char*) malloc(sizeof(char)*100);
	ligne->color = (char*) malloc(sizeof(char)*100);
	strcpy(ligne->code, "1");
	strcpy(ligne->color, "#00FF00");
	ligne->vitesse = 12.0;
	ligne->intervalle = 100;
	ligne->suiv = NULL;


	// Creation de deux connexions
	Une_connexion con1, con2;
	con1.sta_dep = liste->truc;
	con1.sta_arr = liste->suiv->truc;
	con1.ligne = ligne;
	con2.sta_dep = liste->suiv->truc;
	con2.sta_arr = liste->suiv->suiv->truc;
	con2.ligne = ligne;
	
	// Creation des deux trucs
	Un_truc *truc1, *truc2;
	Une_coord coord1;
	Une_coord coord2;
	coord1.lat = 10;
	coord1.lon = 01;
	coord2.lat = 20;
	coord2.lon = 02;
	Tdata data1, data2;
	data1.con = con1;
	data2.con = con2;
	truc1 = creer_truc(coord1, CON, data1, 0.0);
	truc2 = creer_truc(coord2, CON, data2, 0.0);

	printf("Dep: %s , Arr: %s , Ligne: %s \n",con1.sta_dep->data.sta.nom, con1.sta_arr->data.sta.nom, con1.ligne->code );
	printf("Dep: %s , Arr: %s , Ligne: %s \n",con2.sta_dep->data.sta.nom, con2.sta_arr->data.sta.nom, con2.ligne->code );

	printf("Dep: %s , Arr: %s  \n",truc1->data.con.sta_dep->data.sta.nom, truc1->data.con.sta_arr->data.sta.nom  );
	printf("Dep: %s , Arr: %s \n",truc2->data.con.sta_dep->data.sta.nom, truc2->data.con.sta_arr->data.sta.nom );




	Un_elem *liste_con=NULL;
	liste_con = inserer_deb_liste(liste_con, truc1);
	liste_con = inserer_deb_liste(liste_con, truc2);
	Un_elem *tmp = liste_con;
	while (tmp != NULL) {
		printf("%s ; %s \n", tmp->truc->data.con.sta_dep->data.sta.nom, tmp->truc->data.con.sta_arr->data.sta.nom);
		tmp = tmp->suiv;
	}


	detruire_liste_et_truc(liste);
	return 0;
}