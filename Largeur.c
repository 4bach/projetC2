#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Graphe.h"
#include "SVGwriter.h"
#include "entree_sortie.h"
#include "Struct_Liste.h"
#include "Struct_File.h"
#include "Largeur.h"
#include "dijkstra.h"

// Calcul du nombre d'arc minimum
int nbarcsmin(Graphe *G, int u, int v)
{ 

  Sommet *cour;
  Cellule_arete* arr;
  int tmp;
  int voisin;

  // Tableau du nombre de tours effectués pour arriver à un point
  int* visit = ( int* )malloc( (G->nbsom + 1)*sizeof(int) ); 
  int i;

  S_file F; 

  Init_file( &F );

  // Initialisation du tableau visiter
  for ( i = 0; i < G->nbsom + 1; i++ ) 
    visit[i] = -1; 

  visit[u] = 0;

  enfile(&F, u);

//Tant que la file n'est pas vide -> itérer
  while ( !(estFileVide(&F))) { 
	tmp = defile( &F );
	arr = G->T_som[tmp]->L_voisin;

	//Dans chaque point du tableau, parcourir tous ses voisins
	while ( arr != NULL ) { 
		if( tmp == arr->a->v ) voisin = arr->a->u;
		else voisin = arr->a->v;

		//Si le point n'a pas été visité -> additioner 1 au nombre de visite de son père
		if (visit[voisin] == -1 ) {
			visit[voisin] = visit[tmp] + 1;
			enfile(&F,voisin); 
		}
		
		//Si ce point correponds à celui recherhé, renvoyer le nombre de "tours" effectués
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
	
	
	Sommet *cour;
	Cellule_arete* arr;
	int tmp;
	int voisin;

	//Tableau ou chaque élément référence son père
	int* chemin = ( int* )malloc( (G->nbsom + 1)*sizeof(int) ); 
	int* visit = ( int* )malloc( (G->nbsom + 1)*sizeof(int) ); 
	int i;

	S_file F; 

	Init_file( &F );

	for ( i = 0; i < G->nbsom + 1; i++ ) 
		visit[i] = -1; 

	visit[u] = 0;

	enfile(&F, u);

	//Tant que la file n'est pas vide
	while ( !(estFileVide(&F))) { 
		
		tmp = defile( &F );
		arr = G->T_som[tmp]->L_voisin;

		//On visite tous les voisins de chaque point tmp
		while ( arr != NULL ) { 
			
			//Arrete visitée -> recherche du points correspondant
			if( tmp == arr->a->v ) voisin = arr->a->u;
			else voisin = arr->a->v;

			//case du tableau chemin -> reference son père 
			if (visit[voisin] == -1 ) {
				visit[voisin] = visit[tmp] + 1;
				chemin[voisin] = tmp;
				enfile(&F,voisin); 
			}
			
			if( voisin == v ) {
				break;
			}

		arr = arr->suiv;
	}
	

  }
  	//Creation d'une liste des points du chemin
	ListeEntier premier = malloc( sizeof(ListeEntier));
	premier->u = v;
	premier->suiv = NULL;
	tmp = v;

	while( tmp != u ){

		//Dans la case tmp du tableau, il y a le numéro du point précedent
		tmp = chemin[tmp];
		ListeEntier deux = malloc( sizeof(ListeEntier));
		deux->u = tmp;
		deux->suiv = premier;
		premier = deux;
	}
	return premier;
}

//Retourne une liste de tous les chemins correpondant aux commodités
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
	
	//Calcul du chemin de u à v pour chaque commodité
	for( i = 1; i<G->nbcommod; i++ ) {

		Liste_chemin* deux = malloc(sizeof( Liste_chemin ) );
		deux->points = cheminuv( G, liste_commodite[i].e1, liste_commodite[i].e2 );
		deux->suiv = premier;
		premier = deux;

	}

	return premier;
}

//Ecritures de chaque chaine de points dans un fichier
void ecrire_commodites( Graphe* G, char* nomfic ) 
{	
	int cpt;
  	cpt = nbarcsmin( G, 10, 15);
	Liste_chemin* liste = chemin_commodites( G );
	char str[10] = "";
	FILE* f1;
	if( ((f1=fopen(nomfic,"r"))!=NULL) ) {
		remove(nomfic);
		//return;
	}
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
	fclose(f1);
}

//Ecritures de chaque chaine de points dans un fichier
void ecrire_commodites_dijsktra( Graphe* G, char* nomfic ) 
{	
	int cpt;
  	cpt = nbarcsmin( G, 10, 15);
	Liste_chemin* liste = chemin_commodites( G );
	char str[10] = "";
	FILE* f1;
	if( ((f1=fopen(nomfic,"r"))!=NULL) ) {
		remove(nomfic);
		//return;
	}
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
	fclose(f1);
}
//Retourne l'arrête correpsondant à u et v dans le graphe
Arete* recherche_arrete( Graphe* G, int u, int v ) {
	int i;
	Arete* a;
	for( i = 1; i < G->nbsom+1; i++ ) {

		Cellule_arete* tmp = G->T_som[i]->L_voisin;

		while( tmp ) {
			//Si ce sont les mêmes numéros de points> return a
			if( ( (tmp->a->u == u ) && ( tmp->a->v == v)) || ((tmp->a->v == u ) && (tmp->a->u == v) ) )
				return tmp->a;
			tmp = tmp->suiv;
		}
	}
	return NULL;
}

//calcul de la largeur maximale 
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
	
	//On prend une première arrête (doute sur l'utilité)
	sommet1 = GetEntier( f1 );
	Skip( f1 );
	sommet2 =  GetEntier( f1 );
	a = recherche_arrete( G, sommet1, sommet2 );
	a->calc_gamma++;

	//Tant qu'on peut lire sommet 2 -> continue
	while( sommet2 != 0 ) {

		//On prend l'arrête suivante
		sommet1 = sommet2;
		Skip( f1 );
		sommet2 = GetEntier( f1 );

		//Si sommet 2 correspond a la fin de la ligne -> on saute
		if( sommet2 == -1 ) {
			SkipLine( f1 );
			continue;

		//Ensuite sommet 1 =-1, on saute un tour
		} else if( sommet1 == -1 ) continue;
		a = recherche_arrete( G, sommet1, sommet2 );

		//A chaque fois que l'arrete est trouvée, on ajoute 1 à gamma
		a->calc_gamma++;
		if( a->calc_gamma > max ) max = a->calc_gamma;
		
	}

	/*//On recherche le maximum
	for( i = 1; i < G->nbsom; i++ ) {
		Cellule_arete* tmp = G->T_som[i]->L_voisin;
		while( tmp ) {
			if( tmp->a->calc_gamma > max ) max = tmp->a->calc_gamma;
			tmp = tmp->suiv;
		}
	}*/
	fclose(f1);
	return max;
}

//Même principe pour le calcul de longueur
double calcul_longueur( char* nomfic, Graphe* G ) 
{
	double cpt = 0;
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

		//Seul changement, on ajoute a chaque fois qu'on croise l'arrete, sa distance
		a = recherche_arrete( G, sommet1, sommet2 );
		cpt += a->longueur;
	}
	fclose(f1);
	return cpt;
}

















