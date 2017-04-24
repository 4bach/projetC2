#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Graphe.h"
#include "SVGwriter.h"
#include "entree_sortie.h"
#include "Struct_Liste.h"
#include "dijkstra.h"


/*UTILITARES TAS*/

int racine(void){
	return 1;
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
	if hasPere(i)
		return i/2;
	return racine;
}

void init(Tas* t){
	t->n=0;
}
int taille(Tas* t){
	return t->n;
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
	
	float tmp=t->tab[i];
	t->tab[i]=t->tab[j];
	t->tab[j]=tmp;
}

void monter(Tas* t,int i){
	if(! hasPere(i)) return;
	
	int papa=pere(i);
	if(t->tab[papa]>t->tab[i]){
		echanger(t,i,papa);
		monter(t,papa);
	}
}
void plusPetitfils(t,i){
	if(! hasFilsdroit(t,i)){
		return filsGauche(i);
	}
	else{
		int fg=filsGauche(i);
		int fd=filsDroit(i);
		return (t->tab[fg]<t->tab[fd])?fg:fd;
	}
	
}
void descendre(Tas* t,int i){
	if(isFeuille(t,i))return;
	
	int fils=plusPetitfils(t,i);
	if(t->tab[i]>t->tab[fils]){
		echanger(t,fils,i);
		descendre(t,fils);
	}
}
void min(Tas* t){
	return t->tab[racine()];
}
