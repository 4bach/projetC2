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


/*int calcul_longueur( char* nomfic ) 
{
	int cpt = 0;
	int nbligne = 0;
	int tmp = 1;
	int boole = 1;
	FILE* f1;

	if(((f1=fopen(nomfic,"r"))==NULL)){
		printf("Le fichier %s n'existe pas\n",nomfic);
		return 0;
	}

	while( tmp ) {
		tmp = GetEntier( f1 );
		printf( "TMP = %d, CPT = %d, NBLIGNE = %d\n", tmp, cpt, nbligne );
		if( tmp == -1 ) {
			SkipLine( f1 );
			nbligne++;
		}
		else {
			Skip( f1 );
			cpt++;
		}
		printf( "TMP = %d, CPT = %d, NBLIGNE = %d\n", tmp, cpt, nbligne );

	}
	return cpt - nbligne;
}*/

int est_pas_dans_liste(  Cellule_arete* arete, Arete* a ) {

	if( arete == NULL ) return 1;
	Cellule_arete* tmp = arete;

	while( tmp ) {
		if( (a->u == arete->a->u && a->v == arete->a->v ) || (a->v == arete->a->u && a->u == arete->a->v))
			return 0;
		tmp = tmp->suiv;
	}
	return 1;
}
int calcul_longueur( char* nomfic ) 
{
	int cpt = 0;
	int nbligne = 0;
	int tmp = 1;
	FILE* f1;

	int sommet1, sommet2;

	
	if(((f1=fopen(nomfic,"r"))==NULL)){
		printf("Le fichier %s n'existe pas\n",nomfic);
		return 0;
	}

	sommet1 = GetEntier( f1 );
	Skip( f1 );
	sommet2 =  GetEntier( f1 );

	Cellule_arete* arete = malloc( sizeof( Cellule_arete ) );
	arete->suiv = NULL;
	arete->a = malloc( sizeof( Arete ) );
	arete->a->u = sommet1;
	arete->a->v = sommet2;


	while( sommet1 ) {
		
		sommet1 = sommet2;
		Skip( f1 );
		sommet2 = GetEntier( f1 );
		//printf( "sommet1 = %d, sommet2 = %d\n", sommet1, sommet2 );
		if( sommet1 == - 1 || sommet2 == -1 ) {
			SkipLine( f1 );
			continue;
		}
		
		Arete* a = malloc( sizeof( Arete ) );
		a->u = sommet1;
		a->v = sommet2;

		if( est_pas_dans_liste(  arete, a )  ) {
			printf( "sommet1 = %d, sommet2 = %d\n", sommet1, sommet2 );
			Cellule_arete* tmp = malloc( sizeof( Cellule_arete ) );
			tmp->a = a;
			tmp->suiv = arete;
			arete = tmp;
		}
		
	}
	while( arete ) {
		cpt++;
		arete =  arete->suiv;
	}
	return cpt;
}

int calcul_largeur( char* nomfic ) {
		

	return 0;
}
























