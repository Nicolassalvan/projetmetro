#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "abr.h"
#include "truc.h"
#include "liste.h"
#include "ligne.h"



// OK
Un_nabr *creer_nabr(Un_truc *truc) //l’allocation d’un noeud et son initialisation
{
	Un_nabr *arbre =(Un_nabr*)malloc(sizeof(Un_nabr));
	if(arbre==NULL)
	{
		printf("Erreur d'allocation\n");
		return NULL;
	}
	arbre->truc = truc;
	arbre->g = NULL;
	arbre->d = NULL;
	return arbre;
}

// OK mais il manque quelques cas
Un_nabr *inserer_abr(Un_nabr *abr, Un_nabr *n) //insère un noeud à sa place
{
	if(abr==NULL) { //Si l'arbre est vide on retourne juste le noeud n
		return n;
	}
	if (n==NULL) return abr;
	if(strcmp(n->truc->data.sta.nom,abr->truc->data.sta.nom) >= 0){
		abr->d = inserer_abr(abr->d,n);
	}
	else {
		abr->g = inserer_abr(abr->g,n);//Sinon on l'insère comme fils gauche
	}
	return abr;
}

// OK
Un_nabr *construire_abr(Un_elem *liste_sta)
{
	if (liste_sta==NULL) return NULL;
	if (liste_sta->truc==NULL) return NULL;
	Un_nabr *new_arbre = creer_nabr(liste_sta->truc);
	Un_elem *tmp_liste = liste_sta->suiv; //Variable temporaire que l'on fera pointer vers chaque élement de la liste 
	while(tmp_liste!=NULL)//On insère les suivants ensuite à gauche ou à droite
	{
		Un_nabr *noeud = creer_nabr(tmp_liste->truc);
		new_arbre = inserer_abr(new_arbre,noeud);
		tmp_liste = tmp_liste->suiv; //Après avoir inserer le noeud, on considère l'élement suivant de la liste
	}
	return new_arbre;
}

// OK
void detruire_abr(Un_nabr *abr)
{
	if(abr == NULL) return;
	if(abr->g != NULL) detruire_abr(abr->g);
	if(abr->d != NULL) detruire_abr(abr->d);

	free(abr);
}

// OK
Un_truc *chercher_station(Un_nabr *abr, char *nom)
{
	if (abr==NULL) {
		return NULL;
	}
	int comp = strcmp(abr->truc->data.sta.nom, nom);
	if (comp == 0) {
		return abr->truc;
	}
	else if (comp > 0) {
		return chercher_station(abr->g, nom);
	}
	else {
		return chercher_station(abr->d, nom);
	}
}

/*
//Fonction pour voir l'arbre construit
void parcours_prefixe_abr(Un_nabr* abr, int n) {
	if (abr==NULL) return;
	int i;
	for (i=0; i<n ;i++) {
		printf("\t");
	}
	printf("%d: %s\n", n, abr->truc->data.sta.nom);
	parcours_prefixe_abr(abr->g, n+1);
	parcours_prefixe_abr(abr->d, n+1);
} 
*/



Un_elem *lire_connexions(char *nom_fichier,Une_ligne *liste_ligne, Un_nabr *abr_sta)
{
	// In: nom du fichier, liste des lignes du métro, abr contenant toutes les stations
	// Out: liste des connexions (+modifie le tab_con de chaque station et user_val)

	// Ouverture du fichier
	FILE *fic = fopen(nom_fichier,"r");
	if(fic==NULL)
	{
		printf("Erreur ouverture fichier\n");
		return NULL;
	}
	if (liste_ligne == NULL) {
		fclose(fic);
		printf("Erreur: la liste de lignes est vide\n");
		return NULL;
	}
	if (abr_sta == NULL) {
		fclose(fic);
		printf("Erreur: l'abr des stations est vide\n");
		return NULL;
	}

	// Variables temporaires qui vont stocker ce que l'on scanne dans le fichier
	char *code = (char*) malloc(sizeof(char)*100);
	char *station_dep = (char*) malloc(sizeof(char)*100);
	char *station_arr = (char*) malloc(sizeof(char)*100);
	float temps_parcours;
	Une_coord coord0;
	coord0.lon = 0;
	coord0.lat = 0;
	Tdata data;
	int i;

	// Creation de la liste de connexions
	Un_elem *liste_connexions = NULL;

	// On parcourt le fichier contenant les connexions
	while (feof(fic) == 0) {
		// On lit la ligne du fichier
		fscanf(fic, "%100[^;] ; %100[^;] ; %100[^;] ; %f ", code, station_dep, station_arr, &temps_parcours);
		// Problème : on scanne l'espace de fin donc il faut le remplacer par un caractère nul
		code[strlen(code) - 1] = '\0';
		station_arr[strlen(station_arr)-1] = '\0';
		station_dep[strlen(station_dep)-1] = '\0';

		// On vérifie si la ligne existe
		if (chercher_ligne(liste_ligne, code) != NULL) {
			// On crée le truc qui contient la connexion, et on l'insère dans la liste de connexions
			Un_truc *truc_dep;
			Un_truc *truc_arr;
			truc_dep = chercher_station(abr_sta, station_dep);
			truc_arr = chercher_station(abr_sta, station_arr);
			Un_truc *connexion_inserer; 
			data.con.sta_dep = truc_dep;
			data.con.sta_arr = truc_arr;
			data.con.ligne = chercher_ligne(liste_ligne, code);
			connexion_inserer = creer_truc(coord0, CON, data, 0.0);
			// On calcule l'intervalle de temps entre deux stations si la valeur est nulle pour la ligne
			if (connexion_inserer->data.con.ligne->intervalle == 0.0) {
				float distance, lat1, lat2, lon1, lon2;
				// On convertit les coordonnées des stations de départ et d'arrivée en radians
				lat1 = (double) connexion_inserer->data.con.sta_dep->coord.lat * M_PI / 180 ; 
				lon1 = (double) connexion_inserer->data.con.sta_arr->coord.lat * M_PI / 180; 
				lat2 = (double) connexion_inserer->data.con.sta_dep->coord.lon * M_PI / 180; 
				lon2 = (double) connexion_inserer->data.con.sta_arr->coord.lon * M_PI / 180; 
				distance = (float) 6371 * acos(cos(lat1) * cos(lat2) * cos(lon1 - lon2) + sin(lat1) * sin(lat2));
				connexion_inserer->data.con.ligne->intervalle =  distance / (60 * connexion_inserer->data.con.ligne->vitesse); // min
			}
			// On modifie le tableau de connexions, et on incrémente le nb_connexions pour chaque station

			// Pour ce faire, on commence par incrémenter le nombre de connexions 

			truc_dep->data.sta.nb_con = truc_dep->data.sta.nb_con + 1; 
			truc_dep->data.sta.Tab_con = (Un_truc**) realloc(truc_dep->data.sta.Tab_con, truc_dep->data.sta.nb_con*sizeof(Un_truc*));
			truc_dep->data.sta.Tab_con[truc_dep->data.sta.nb_con-1] = connexion_inserer;
			
			// On insère la connexion dans la liste
			liste_connexions = inserer_deb_liste(liste_connexions, connexion_inserer);
		}
	}
	// On libère la mémoire allouée pour les variables temporaires
	free(code);
	free(station_arr);
	free(station_dep);
	fclose(fic);
	return liste_connexions;
}