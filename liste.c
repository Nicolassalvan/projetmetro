#include <stdio.h>
#include <stdlib.h>
#include "truc.h"
#include "liste.h"
#include "abr.h"
#include <string.h>

// OK
Un_elem *inserer_liste_trie(Un_elem *liste, Un_truc *truc)
{
	// In: liste chainée de type Un_elem, pointeur vers un truc
	//Out: liste chainée avec truc inséré 
	
	// Si on n'insère rien, on renvoie liste
	if(truc==NULL) return liste;

	// On commence par créer Un_elem qui pourra être inséré dans la liste, et qui 
	// pointe vers la même adresse que truc
	Un_elem *truc_insert = (Un_elem *)malloc(sizeof(Un_elem));

	//On vérifie que le malloc a fonctionné
	if (truc_insert == NULL) return liste;
	truc_insert->truc = truc;
	truc_insert->suiv =NULL;

	// Si la liste est NULL ou que liste->truc est NULL on renvoie truc_insert :
	// C'est le cas lorsque la liste n'est pas initialisée
	if((liste==NULL)||(liste->truc == NULL)) {
		return truc_insert;
	}

	// Cas 1 : truc_insert est à insérer au début de la liste
	if(truc->user_val < liste->truc->user_val)
	{
		truc_insert->suiv = liste;
		return truc_insert;
	}
	//Cas 2 : insertion à la fin ou au milieu de la liste
	Un_elem	*tmp = liste;
	int condition = 0;
	while(condition == 0) //T que user_val de truc < user_val de lélément courant de la liste
	{
		if (tmp->suiv !=NULL) {
			if((truc->user_val) >= (tmp->suiv->truc->user_val)) 
			{
				tmp =tmp->suiv;
			}
			else 
			{
				condition = 1;
			}
		} 
		else 
		{
			condition = 1;
		}
	}
	// Si user_val de truc > à tous les userval de la liste 
	// on l'insère à la fin de la liste
	if(tmp->suiv == NULL) 
	{
		tmp->suiv = truc_insert;
	}
	else
	{
		truc_insert->suiv = tmp->suiv;
		tmp->suiv = truc_insert;
	}
	return liste;
}

// OK
Un_elem *lire_stations(char* nom_fichier) {
	//In: nom du fichier contenant les stations et leurs coos GPS
	//Out: liste contenant les stations du fichier 
	FILE *fic=fopen(nom_fichier, "r");
	if (fic == NULL) {
		printf("Erreur ouverture fichier\n");
		return NULL;
	}
	Un_elem *liste = (Un_elem*) malloc(sizeof(Un_elem));
	if (liste == NULL) {
		printf("Erreur d'allocation mémoire liste");
		return NULL;
	}
	Une_coord coord;
	int lastchar;
	char *nom= (char*)malloc(sizeof(char)*100);
	while (feof(fic) == 0) {
		Tdata data;
		//Le dernier caractère du nom est \n, il faut donc le supprimer
		fscanf(fic, "%f ; %f ; %100[^\n]",&(coord.lon), &(coord.lat), nom);
		lastchar = (int) strlen(nom);
		if (nom[lastchar] == '\n') {
			nom[lastchar] = '\0'; 
		}
		data.sta.nb_con = 0;
		data.sta.Tab_con = NULL;
		data.sta.con_pcc = NULL;
		Un_truc *truc=creer_truc(coord, STA, data, 0.0);
		truc->data.sta.nom = (char *)malloc(100 * sizeof(char));
		strcpy(truc->data.sta.nom, nom);
		liste = inserer_liste_trie(liste, truc);
	}
	free(nom);
	fclose(fic);
	return liste;
}

void detruire_liste(Un_elem *liste)
{
	if(liste==NULL) return;
		Un_elem *tmp= liste->suiv;
		free(liste);
		detruire_liste(tmp);
}

void detruire_liste_et_truc(Un_elem *liste)
{
 	Un_elem *tmp = liste, *tmp2=NULL;
    while (tmp != NULL)
    {
        detruire_truc(tmp->truc);
        tmp2 = tmp;
        tmp = tmp->suiv;
        free(tmp2);
    }
}

void limite_zones(Un_elem* liste, Une_coord* limite_no, Une_coord* limite_se) {
	float lonmax, lonmin, latmax, latmin;
	if (liste == NULL) {
		return;
	}
	//Coos de la limite no: lonmax, latmin
	//Coos de la limite se: lonmin, latmax
	lonmax = liste->truc->coord.lon;
	lonmin = lonmax;
	latmax = liste->truc->coord.lat;
	latmin = latmax;
	while(liste !=NULL ) {
		if(latmin > liste->truc->coord.lat) {
			latmin = liste->truc->coord.lat; 
		}
		if(latmax < liste->truc->coord.lat) {
			latmax = liste->truc->coord.lat; 
		}
		if (lonmin > liste->truc->coord.lon) {
			lonmin = liste->truc->coord.lon;
		}
		if (lonmax > liste->truc->coord.lon) {
			lonmax = liste->truc->coord.lon;
		}
		liste = liste->suiv;
	}
	limite_no->lat = latmin;
	limite_no->lon = lonmax;
	limite_se->lat = latmax;
	limite_se->lon = lonmin;
}

// OK
void ecrire_liste(FILE *flux, Un_elem *liste) {
	if (flux == NULL) {
		printf("Erreur création de fichier\n");
		return;
	}
	while (liste != NULL) {
		fprintf(flux, "%f ; %f ; %s\n", liste->truc->coord.lon, liste->truc->coord.lat, liste->truc->data.sta.nom);
		liste = liste->suiv;
	}
}

// OK
Un_elem *inserer_deb_liste(Un_elem *liste, Un_truc *truc)
{ 
	// In: liste de connexions, connexion (truc) à insérer
	// Out: liste de connextions avec truc inséré

	if (truc==NULL) return liste;

	Un_elem* liste_insert = (Un_elem*) malloc(sizeof(Un_elem));
	liste_insert->truc = truc;
	liste_insert->suiv = NULL;
	if (liste == NULL) return liste_insert;

	Un_elem *tmp = liste;
	while (tmp->suiv != NULL) {
		tmp = tmp->suiv;
	}
	tmp->suiv = liste_insert;
	return liste;
} 