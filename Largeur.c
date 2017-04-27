#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Graphe.h"
#include "SVGwriter.h"
#include "entree_sortie.h"
#include "Struct_Liste.h"
#include "Struct_File.h"
#include "Largeur.h"

int nbarcsmin(Graphe *G, int u, int v)
{ 

  Sommet *cour;
  Cellule_arete* arr;
  int tmp;
  int voisin;

  int* visit = ( int* )malloc( (G->nbsom + 1)*sizeof(int) ); 
  int i;

  S_file F; 

  Init_file( &F );

  for ( i = 0; i < G->nbsom + 1; i++ ) 
    visit[i] = -1; 

  visit[u] = 0;

  enfile(&F, u);

  while ( !(estFileVide(&F))) { 
	tmp = defile( &F );
	arr = G->T_som[tmp]->L_voisin;
	while ( arr != NULL ) { 
		if( tmp == arr->a->v ) voisin = arr->a->u;
		else voisin = arr->a->v;

		if (visit[voisin] == -1 ) {
			visit[voisin] = visit[tmp] + 1;
			enfile(&F,voisin); 
		}
		
		if( voisin == v ) {
			return visit[voisin];
		}

		arr = arr->suiv;
	}

  } 
  return 0;
}

ListeEntier cheminuv( Graphe *G, int u, int v )
{ 
	
	
	//faire un tableau avec tous les elements, chaque case du tableau references la position de son pere
	//si voisin == v , alors faire une boucle qui creer la liste des elements
	// en allant progressivement vers son pere, 
	Sommet *cour;
	Cellule_arete* arr;
	int tmp;
	int voisin;
	int* chemin = ( int* )malloc( (G->nbsom + 1)*sizeof(int) ); 
	int* visit = ( int* )malloc( (G->nbsom + 1)*sizeof(int) ); 
	int i;

	S_file F; 

	Init_file( &F );

	for ( i = 0; i < G->nbsom + 1; i++ ) 
		visit[i] = -1; 

	visit[u] = 0;

	enfile(&F, u);

	while ( !(estFileVide(&F))) { 
		tmp = defile( &F );
		//printf("1" );
		arr = G->T_som[tmp]->L_voisin;
		while ( arr != NULL ) { 
			//printf("2" );
			if( tmp == arr->a->v ) voisin = arr->a->u;
			else voisin = arr->a->v;

			if (visit[voisin] == -1 ) {
				//printf("voisin visité\n" );
				visit[voisin] = visit[tmp] + 1;
				chemin[voisin] = tmp;
				enfile(&F,voisin); 
			}
			
			if( voisin == v ) {
				//printf("u == v \n" );
				break;
			}

		arr = arr->suiv;
	}
	

  }
	ListeEntier premier = malloc( sizeof(ListeEntier));
	premier->u = v;
	premier->suiv = NULL;
	tmp = v;

	while( tmp != u ){
		tmp = chemin[tmp];
		ListeEntier deux = malloc( sizeof(ListeEntier));
		deux->u = tmp;
		deux->suiv = premier;
		premier = deux;
	}
	return premier;
}

Liste_chemin* chemin_commodites( Graphe* G ) 
{

	if( G == NULL ) {
		return NULL;
	}
	int i;
	Commod *liste_commodite = G->T_commod;

	Liste_chemin* premier = malloc(sizeof( Liste_chemin ) );
	premier->points = cheminuv( G, liste_commodite[i].e1, liste_commodite[i].e2 );
	premier->suiv = NULL;
	
	for( i = 1; i<G->nbcommod; i++ ) {

		Liste_chemin* deux = malloc(sizeof( Liste_chemin ) );
		deux->points = cheminuv( G, liste_commodite[i].e1, liste_commodite[i].e2 );
		deux->suiv = premier;
		premier = deux;

	}

	return premier;
}

void ecrire_commodites( Graphe* G, char* nomfic ) 
{
	Liste_chemin* liste = chemin_commodites( G );
	char str[10] = "";
	FILE* f1;
	if(((f1=fopen(nomfic,"w"))==NULL)){
		printf("Le fichier %s ne s'ouvre pas\n",nomfic);
		return;
	}
	while( liste ) {
		ListeEntier points = liste->points;
		while( points ) {
			sprintf(str,"%d ",points->u);
			fprintf(f1,"%s",str);

			points = points->suiv;
		}
		fprintf(f1,"-1\n");
		liste = liste->suiv;
	}
}


/*int calcul_longueur( Graphe* G ) 
{
	int i;
	int cpt = 0;
	for( i = 1; i < G->nbsom; i++ ) {

		Cellule_arete* tmp = G->T_som[i]->L_voisin;
		while( tmp ) {
			cpt+= tmp->a->longueur;
			tmp = tmp->suiv;
		}
	}
	return cpt/2;
}*/



/*int calcul_largeur( Graphe* G ) 
{

	int i;
	int max = 0;

	for( i = 1; i < G->nbsom; i++ ) {
		Cellule_arete* tmp = G->T_som[i]->L_voisin;
		while( tmp ) {
			tmp->a->calc_gamma++;
			tmp = tmp->suiv;
		}
	}

	for( i = 1; i < G->nbsom; i++ ) {
		Cellule_arete* tmp = G->T_som[i]->L_voisin;
		while( tmp ) {
			if( tmp->a->calc_gamma > max ) max = tmp->a->calc_gamma;
			tmp = tmp->suiv;
		}
	}
	return max;
}*/

//peut etre fait de maniere bcp + rapide -> on cherche un des points dans le tableau, puis on cherche l'autre dans ses voisins
Arete* recherche_arrete( Graphe* G, int u, int v ) {
	int i;
	Arete* a;
	for( i = 1; i < G->nbsom+1; i++ ) {
		//printf( "i = %d \n", i );
		Cellule_arete* tmp = G->T_som[i]->L_voisin;
		while( tmp ) {
			//printf( "U = %d, V = %d, AU = %d, AV = %d\n", u, v, tmp->a->u, tmp->a->v );
			if( ( (tmp->a->u == u ) && ( tmp->a->v == v)) || ((tmp->a->v == u ) && (tmp->a->u == v) ) )
				return tmp->a;
			tmp = tmp->suiv;
		}
	}
	return NULL;
}

int calcul_largeur( char* nomfic, Graphe* G ) 
{
	int max = 0;
	int i;
	FILE* f1;
	int sommet1, sommet2;
	Arete* a;
	
	if(((f1=fopen(nomfic,"r"))==NULL)){
		printf("Le fichier %s n'existe pas\n",nomfic);
		return 0;
	}
	
	sommet1 = GetEntier( f1 );
	//printf( "sommet 1 = %d \n", sommet1 );
	Skip( f1 );
	sommet2 =  GetEntier( f1 );
	//printf( "sommet 2 = %d \n", sommet2 );
	a = recherche_arrete( G, sommet1, sommet2 );
	a->calc_gamma++;

	while( sommet2 != 0 ) {
		sommet1 = sommet2;
		Skip( f1 );
		sommet2 = GetEntier( f1 );
		//printf( "sommet 1 = %d \n", sommet1 );
		//printf( "sommet 2 = %d \n", sommet2 );
		//printf( "sommet1 = %d, sommet2 = %d\n", sommet1, sommet2 );
		if( sommet2 == -1 ) {
			SkipLine( f1 );
			//printf("\n");
			continue;
		} else if( sommet1 == -1 ) continue;
		//printf( "S1 = %d, S2 = %d ||", sommet1, sommet2 );
		a = recherche_arrete( G, sommet1, sommet2 );
		a->calc_gamma++;
		
	}
	for( i = 1; i < G->nbsom; i++ ) {
		//printf( "i = %d \n", i );
		Cellule_arete* tmp = G->T_som[i]->L_voisin;
		while( tmp ) {
			if( tmp->a->calc_gamma > max ) max = tmp->a->calc_gamma;
			tmp = tmp->suiv;
		}
	}
	return max;
}

int calcul_longueur( char* nomfic, Graphe* G ) 
{
	int cpt = 0;
	int i;
	FILE* f1;
	int sommet1, sommet2;
	Arete* a;
	
	if(((f1=fopen(nomfic,"r"))==NULL)){
		printf("Le fichier %s n'existe pas\n",nomfic);
		return 0;
	}
	
	sommet1 = GetEntier( f1 );
	Skip( f1 );
	sommet2 =  GetEntier( f1 );
	a = recherche_arrete( G, sommet1, sommet2 );

	while( sommet2 != 0 ) {

		sommet1 = sommet2;
		Skip( f1 );
		sommet2 = GetEntier( f1 );

		if( sommet2 == -1 ) {
			SkipLine( f1 );
			continue;
		} else if( sommet1 == -1 ) continue;

		a = recherche_arrete( G, sommet1, sommet2 );
		cpt += a->longueur;
	}
	
	return cpt;
}

















