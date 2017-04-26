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
	if (hasPere(i))
		return i/2;
	return racine();
}

Tas* init_tas(int n){
	Tas* t=(Tas*)malloc(sizeof(Tas));
	t->nb_tot=n;
	t->nb_elem=0;
	t->elem=NULL;
	t->tab=(int*)malloc(n*sizeof(int));
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
	t->elem[i]->dist=t->elem[j]->dist;
	t->elem[i]->u=t->elem[j]->u;
	t->elem[j]->dist=tmp;
	
	t->elem[j]->u=Tmp;
}

void monter(Tas* t,int i){
	if(! hasPere(i)) return;
	
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

void insert(Tas *t,float dist,int s){
	if (t->nb_elem<t->nb_tot){
		t->nb_elem++;
		t->elem[t->nb_elem]->dist=dist;
		t->elem[t->nb_elem]->u=s;
		monter(t,t->nb_elem);
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

void init_lambda(int taille,double* lambda){
	
	int i;
	
	for (i = 0; i < taille; i++)
	{
		lambda[i]= DBL_MAX;
		
	}
}

void init_pred(int taille,int* pred){
	
	int i;
	for (i = 0; i < taille; i++)
	{
		pred[i]=-1;
	}
	
}
void init_marque(int taille,int* marque){
	int i;
	for (i = 0; i < taille; i++)
	{
		marque[i]=0;
	}
	
}
	


void Dijkstra(Graphe* G,int u,int* prev,double* lambda){
	/*initialistation*/
	
	init_lambda(G->nbsom,lambda);
	int marque[G->nbsom];
	init_marque(G->nbsom,marque);
	init_pred(G->nbsom,prev);
	Tas* t=init_tas(G->nbsom);
	
	
		
}
