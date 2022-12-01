#ifndef LIGNE_H
#define LIGNE_H

typedef struct _une_ligne
{
	char *code; //Le nom de la ligne 
	char *color; //La couleur de la ligne 
	float vitesse; //Vitesse moyenne des rames en km/h
	float intervalle; //Intervalle moyen entre 2 rames
	struct _une_ligne *suiv;
}Une_ligne;

Une_ligne* inserer_ligne(Une_ligne *liste,Une_ligne *ligne_insert) ;
Une_ligne *lire_lignes(char *nom_fichier);
void afficher_lignes(Une_ligne *ligne);
void detruire_lignes(Une_ligne *lligne);
Une_ligne *chercher_ligne(Une_ligne *lligne, char *code);

#endif
