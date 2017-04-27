#ifndef __LARGEUR_H__
#define __LARGEUR_H__
#include "Graphe.h"
#include "Struct_Liste.h"

typedef struct liste_chemin {
	ListeEntier points;
	struct liste_chemin* suiv;
} Liste_chemin;



Liste_chemin* chemin_commodites( Graphe* G );
int nbarcsmin(Graphe *G, int u, int v);
ListeEntier cheminuv( Graphe *G, int u, int v );
void ecrire_commodites( Graphe* G, char* nomfic );
void ecrire_commodites_dijsktra( Graphe* G, char* nomfic );
double calcul_longueur( char* nomfic, Graphe* G );
int calcul_largeur( char* nomfic, Graphe* G );

#endif