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
	return NULL;
	/*
	//Créer les trucs correspondants
	FILE *fic = fopen(nom_fichier,'r');
	if(fic==NULL)
	{
		printf("Erreur ouverture fichier\n");
		return NULL;
	}
	Un_elem *liste = (Un_elem*)malloc(sizeof(Un_elem));
	if(liste==NULL)
	{
		printf("Erreur d'allocation mémoire liste");
		return NULL;
	}
	*/

}
