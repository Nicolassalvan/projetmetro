#include <stdio.h>
#include <stdlib.h>
#include "truc.h"
#include "coord.h"

// OK
Un_truc *creer_truc(Une_coord coord, Ttype type, Tdata data, double uv)
{
	Un_truc *truc = (Un_truc*)malloc(sizeof(Un_truc));
	if(truc==NULL)
	{
		printf("Erreur d'allocation mémoire");
		return NULL;
	}
	truc-> coord = coord;
	truc-> type = type;
	truc-> data = data;
	truc-> user_val = (float)uv;
	return truc;
}

// OK
void detruire_truc(Un_truc *truc)
{
 	if (truc == NULL) return;
 	int i;
 	if((truc->type) == STA) //Si c'est une station
	{
		free(truc->data.sta.nom);
		if (truc->data.sta.con_pcc != NULL)
        {
            free(truc->data.sta.con_pcc);
        }
		if(truc->data.sta.Tab_con !=NULL)
		{
			for(i=0; i < (truc->data.sta.nb_con); i++) {
				free(truc->data.sta.Tab_con[i]);
			}
			free(truc->data.sta.Tab_con);
		}
	 	free(truc); //On désalloue la station
	}

	 else //Si c'est une connexion
	{
		free(truc); //On désalloue la connexion  
	}
}