#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"liste.h"
#include"truc.h"
#include"abr.h"
#include"ligne.h"

//On crée la fonction inserer_ligne dont on aura besoin pour créer une liste de ligne 
Une_ligne* inserer_ligne(Une_ligne *liste,Une_ligne *ligne_insert) //OK
{
	if(liste==NULL) //Si la liste est vide on renvoie juste la ligne
	{
		return ligne_insert;
	}
	if(ligne_insert==NULL) //Si la ligne est Null on renvoie notre liste de base
	{
		return liste;
	}
	// Si on est dans aucun de ces 2 cas on plca la ligne en fonction de son code
	Une_ligne *tmp = liste ; //Cette variable stocke la tête de la liste
	while(tmp->suiv !=NULL) //Tant qu'on est pas arrivé à la fin de la liste
	{
		tmp=tmp->suiv; //On considère l'élément suivant
	}
	tmp->suiv=ligne_insert;
	return liste;
}

Une_ligne *lire_lignes(char *nom_fichier) // OK
{
	//In: nom du fichier contenant les lignes
	//Out: liste contenant les lignes
	//on ouvre le fichier
	FILE* fic = fopen (nom_fichier , "r"); //On l'ouvre en mode lecture
	
	//on vérifie si le fichier a bien été ouvert
	if (fic == NULL)
	{
		printf("Erreur ouverture fichier\n");
		return NULL;
	}

	Une_ligne *liste = NULL;

	char *code = (char*)malloc(sizeof(char)*100); //Mémoire pour le code temp
	char *color = (char*)malloc(sizeof(char)*100); //Mémoire ppur la couleur temp
	float vitesse; //Variable temp contenant la vitesse
	float intervalle; //Variable temp contenant l'intervalle

	while(feof(fic)==0) //Tant qu'on a pas parcouru tout le fichier
	{
		// Allocation de la mémoire pour la nouvelle ligne
		Une_ligne* ligne = (Une_ligne*) malloc (sizeof(Une_ligne)); 
		ligne->color = (char*) malloc(sizeof(char)*10);
		ligne->code = (char*) malloc(sizeof(char)*100);
		// On récupère les données
		fscanf(fic,"%100[^ ;] ; %f ; %f ; %100[^\n]",code,&vitesse,&intervalle,color); //On récupère les données du fichier et on les stocke
		//On initiliase notre ligne avec les élément récupérés
		strcpy(ligne->code,code);
		strcpy(ligne->color,color);
		ligne->color[7] = '\0';
		ligne->vitesse=vitesse;
		ligne->intervalle=intervalle;
		ligne->suiv=NULL;
		liste = inserer_ligne(liste,ligne);
	}
	free(color);
	free(code);
	return liste;

}
	


void afficher_lignes(Une_ligne *ligne) // OK
{
	//définition des variables locales
	Une_ligne* temp = NULL;
	//on vérifie si ligne n'est pas vide
	if (ligne == NULL)
	{
		printf("la liste de ligne est vide .\n");
	}
	else 
	{
		//on affecte ligne à temp 
		temp = ligne ;
		//on parcourt la liste de ligne 
		while (temp != NULL)
		{
			printf("%s ; %f ; %f ; %s\n",temp->code , temp->vitesse , temp->intervalle , temp->color);
			temp = temp -> suiv;
		}
	}
}

void detruire_lignes(Une_ligne *lligne) // OK
{
	if(lligne==NULL) return; //Si la liste est déja vide
	Une_ligne *tmp=lligne->suiv;
	free(lligne);
	detruire_lignes(tmp);	
}

Une_ligne *chercher_ligne(Une_ligne *lligne, char *code) // OK
{
	if(lligne==NULL) 
	{ 
		printf("La liste est nulle\n");
		return NULL;
	}

	Une_ligne *tmp=lligne;
	while(tmp!=NULL)
	{
		if (strcmp(tmp->code,code)==0) return tmp;
		tmp=tmp->suiv;
	}
	printf("Cette ligne n'est pas dans la liste.\n");
	return NULL; //Si le code ne se trouve pas dans la liste
}