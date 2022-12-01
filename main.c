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
	Une_ligne* liste = NULL;
	/*
	FILE* fic = fopen("ligne.csv", "r");
	float vitesse, intervalle;
	Une_ligne *ligne_insert = (Une_ligne*) malloc(sizeof(Une_ligne));
	char *code=(char*) malloc(sizeof(char)*100), *color=(char*) malloc(sizeof(char)*100);
	ligne_insert->code = (char*) malloc(sizeof(char)*100);
	ligne_insert->color = (char*) malloc(sizeof(char)*100);
	fscanf(fic,"%100[^ ;] ; %f ; %f ; %100[^\n]",code,&vitesse,&intervalle,color);
	printf("%s, %s, %f, %f\n", code, color, vitesse, intervalle);
	strcpy(ligne_insert->code,code);
	strcpy(ligne_insert->color,color);
	ligne_insert->vitesse=vitesse;
	ligne_insert->intervalle=intervalle;
	ligne_insert->suiv=NULL;
	liste = inserer_ligne(liste,ligne_insert);
	printf("%s, %s, %f, %f\n", liste->code, liste->color, liste->vitesse, liste->intervalle);

	fclose(fic);
	*/

	liste = lire_lignes("ligne.csv");
	
	Une_ligne *tmp=liste;
	while (tmp !=NULL) {
		printf("%s ; %f ; %f ; %s\n", tmp->code, tmp->vitesse, tmp->intervalle, tmp->color);
		tmp = tmp->suiv;
	}
	Une_ligne *ligne1=NULL;
	ligne1 = chercher_ligne(liste, "1");
	printf("%s\n", ligne1->code);
	detruire_lignes(liste);

	return 0;
}