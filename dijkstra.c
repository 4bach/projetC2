#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include "Graphe.h"
#include "SVGwriter.h"
#include "entree_sortie.h"
#include "Struct_Liste.h"
#include "dijkstra.h"


/*UTILITARES TAS*/

int racine(void){
	return 0;
}

int hasPere(int i){
	return i!=racine();
}

int filsGauche(int i){
	return 2*i;
}

int filsDroit(int i){
	return 2*i+1;
}
int pere(int i){
	if (i>1)
		return i/2;
	return -1;
}


Tas* init_tas(int n){
	Tas* t=(Tas*)malloc(sizeof(Tas));
	t->nb_tot=n;
	t->nb_elem=0;
	t->elem=(Tas_elem**)malloc((n+1)*sizeof(Tas_elem*));
	t->tab=(int*)malloc((n+1)*sizeof(int));
	init_tab_som(t);
	return t;
}
int taille(Tas* t){
	return t->nb_elem;
}

int isNoeud(Tas* t, int i){
	return i<=taille(t);
	
}

int hasFilsgauche(Tas* t, int i){
	return isNoeud(t,filsGauche(i));
}

int hasFilsdroit(Tas* t, int i){
	return isNoeud(t,filsDroit(i));
}

int Estfeuille(Tas* t, int i){
	return ! hasFilsgauche(t,i);
}

void echanger(Tas* t, int i,int j){
	
	double tmp=t->elem[i]->dist;
	int Tmp=t->elem[i]->u;
	/* maj du tableau de sommet*/
	int temp=t->tab[Tmp];
	t->tab[Tmp]=t->tab[t->elem[j]->u];
	t->tab[t->elem[j]->u]=temp;
	/*.........*/
	t->elem[i]->dist=t->elem[j]->dist;
	t->elem[i]->u=t->elem[j]->u;
	t->elem[j]->dist=tmp;
	t->elem[j]->u=Tmp;
}

void monter(Tas* t,int i){
	if(i<=1) return;
	
	int papa=pere(i);
	if(t->elem[papa]->dist >t->elem[i]->dist){
		echanger(t,i,papa);
		monter(t,papa);
	}
}
int plusPetitfils(Tas* t,int i){
	if(! hasFilsdroit(t,i)){
		return filsGauche(i);
	}
	else{
		int fg=filsGauche(i);
		int fd=filsDroit(i);
		return (t->elem[fg]->dist < t->elem[fd]->dist)?fg:fd;
	}
	
}

int Tasvide(Tas* t){
	
	return t->nb_elem==0;
}

void descendre(Tas* t,int i){
	if(Estfeuille(t,i))return;
	
	int fils=plusPetitfils(t,i);
	if(t->elem[i]->dist>t->elem[fils]->dist){
		echanger(t,fils,i);
		descendre(t,fils);
	}
}

Tas_elem* min(Tas* t){
	return t->elem[racine()];
}

void insert(Tas *t,double dist,int s){
	if (t->nb_elem<t->nb_tot){
		t->nb_elem++;
		Tas_elem* elem=(Tas_elem*)malloc(sizeof(Tas_elem));
		elem->u=s;
		elem->dist=dist;
		t->elem[t->nb_elem]=elem;
		t->tab[s]=t->nb_elem;
		monter(t,t->nb_elem);
		t->nb_elem++;
	}
	else{
		printf("tas plein\n");
	}
}

Tas_elem* suppMin(Tas* t){
	if(t->nb_elem==0){
		printf("Tas vide\n");
		return NULL;
	}
	Tas_elem* min=t->elem[racine()];
	echanger(t,t->nb_elem,racine());
	t->nb_elem--;
	descendre(t,racine());
	return min;
}

int recherche(Tas* t,int s){
	
		return t->tab[s];
}
void supp_elem(Tas*t, int i){
	if(t->nb_elem==0)
		return;
	echanger(t,t->nb_elem,t->tab[i]);
	t->nb_elem--;
	descendre(t,t->tab[i]);
}

/*ALGO DIJKSTRA*/

void init_lambda(int taille,double* lambda,int s){
	
	int i;
	for (i = 1; i <= taille; i++)
	{
		lambda[i]= DBL_MAX;
		
	}
	lambda[s]=0;
}

void init_pred(int taille,int* pred){
	
	int i;
	for (i = 1; i <= taille; i++)
	{
		pred[i]=-1;
	}
	
}
void init_marque(int taille,int* marque){
	int i;
	for (i = 1; i <= taille; i++)
	{
		marque[i]=0;
	}
	
}
void init_tab_som(Tas* t){
	int taille= t->nb_tot;
	int i;
	for (i = 1; i <=taille; i++)
	{
		t->tab[i]=-1;
	}
}


void Dijkstra(Graphe* G,int u,int* prev,double* lambda){
	/*initialistation*/
	
	init_lambda(G->nbsom,lambda,u);
	int marque[G->nbsom];
	init_marque(G->nbsom,marque);
	init_pred(G->nbsom,prev);
	Tas* t=init_tas(G->nbsom);
	Tas_elem* min;
	insert(t,0,u);
	marque[u]=1;

	/*......*/
	Sommet* courant_som;
	Cellule_arete* courant_a;
	int num_som;
	while(! Tasvide(t)){
		min=suppMin(t);
		marque[min->u]=1;
		courant_som=G->T_som[min->u];
		courant_a=courant_som->L_voisin;
		while(courant_a){
			
			/* pour ne pas se tromper de numero de sommet */
			if(courant_a->a->v==min->u)
				num_som=courant_a->a->u;
			else
				num_som=courant_a->a->v;
			/*....................*/
			if(marque[num_som]==0){
				
				if(lambda[num_som]>lambda[min->u]+courant_a->a->longueur){
					lambda[num_som]=lambda[min->u]+courant_a->a->longueur;
					prev[num_som]=min->u;
					insert(t,num_som,lambda[num_som]);
					
				}
			}
			courant_a=courant_a->suiv;
		}
				
				
				
	}	
}
	
/*Affichage*/

void affiche_prev(int* prev,int taille){
	int i;
	for (i =1; i <= taille; i++)
	{
		printf("%d ",prev[i]);
	}
	printf("\n");
}

void affiche_lambda(double* lambda,int taille){
	int i;
	for (i =1; i <= taille; i++)
	{
		printf("%f ",lambda[i]);
	}
	printf("\n");
	
	
	
}
	
		
